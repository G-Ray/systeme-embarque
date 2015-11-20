/*
 * Author: Geoffrey Bonneville <geoffrey.bonneville@gmail.com>
 * TP3
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define ITERATIONS 100

static sem_t *sem1, *sem2; //for fork
static sem_t s1, s2; //for threads

/*
 La mesure réalisée indiquera le nombre de nanosecondes/μsecondes /millisecondes/secondes
(selon l'unité utilisée par la fonction de mesure du temps que vous aurez utilisée)
nécessaires, en moyenne, pour effectuer chacune des opérations ci-dessus. On pourra
éventuellement fournir, un temps minimum et un temps maximum.
*/

struct timespec diff(struct timespec start, struct timespec end)
{
	struct timespec tmp;

        if ((end.tv_nsec-start.tv_nsec)<0) {
		tmp.tv_sec = end.tv_sec-start.tv_sec-1;
		tmp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		tmp.tv_sec = end.tv_sec-start.tv_sec;
		tmp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}

        return tmp;
}

void *my_thread()
{
        pthread_exit(NULL);
}

/*  Création et attente de la terminaison d'une thread, dont la seule fonction est de se terminer
immédiatement. */
void bench_thread()
{
	struct timespec elapsed,
			ts_start,
			ts_end;

	unsigned long total = 0;
	int i;
	int rc;
	pthread_t thread;

	/* Bench threads */
	printf("Benchmarking pthread...\n");
	for(i=0; i<ITERATIONS; i++) {
		/* Point initial avant la creation de la thread */
		clock_gettime(CLOCK_REALTIME, &ts_start);

		rc = pthread_create(&thread, NULL, my_thread, NULL);
	        if(rc) {
	                perror("pthread");
	                exit(EXIT_FAILURE);
	        }

        	pthread_join(thread, NULL);
		/* point final après terminaison de la thread */
		clock_gettime(CLOCK_REALTIME, &ts_end);
		elapsed = diff(ts_start, ts_end);
		total += elapsed.tv_sec + elapsed.tv_nsec;
	}

	printf("\tMean time elapsed after %d iterations = %ldus\n", ITERATIONS, total/ITERATIONS/1000);
}

/* Création et attente de la terminaison d'un processus dont la seule fonction est de se terminer
immédiatement */
void bench_fork()
{
	struct timespec elapsed,
			ts_start,
			ts_end;

	unsigned long total = 0;
	int i;
	pid_t pid;
	int return_status;

	printf("Benchmarking fork...\n");
	for(i=0; i<ITERATIONS; i++) {
		/* Point initial avant la creation du processus */
		clock_gettime(CLOCK_REALTIME, &ts_start);

		pid = fork();
		if (pid < 0) {
			perror("fork!");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) { //child
			exit(0);
		}
		else { //parent
			waitpid(pid, &return_status, 0);
			/* point final après terminaison de la thread */
			clock_gettime(CLOCK_REALTIME, &ts_end);
		}

		elapsed = diff(ts_start, ts_end);
		total += elapsed.tv_sec + elapsed.tv_nsec;
	}
	printf("\tMean time elapsed after %d iterations = %ldus\n", ITERATIONS, total/ITERATIONS/1000);
}

void bench_context_fork()
{
	struct timespec elapsed,
			ts_start,
			ts_end;

	int i;
	int return_status;
	pid_t pid;
	//sem_t *sem1, *sem2;

	if ((sem1 = sem_open("sem1", O_CREAT, 0644, 1)) == SEM_FAILED) {
		perror("semaphore initialization");
		exit(1);
	}

	if ((sem2 = sem_open("sem2", O_CREAT, 0644, 1)) == SEM_FAILED) {
		perror("semaphore initialization");
		exit(1);
	}

	printf("Benchmarking context switches for fork...\n");
	/* Debut de la mesure */
	clock_gettime(CLOCK_REALTIME, &ts_start);

	pid = fork();

	if (pid < 0) {
		perror("fork!");
		exit(EXIT_FAILURE);
	}

	for(i=0; i<ITERATIONS; i++) {
		if (pid == 0) { //child
			sem_wait(sem1);
			sem_post(sem2);
		}
		else { //parent
			sem_wait(sem2);
			sem_post(sem1);
		}
	}

	if (pid == 0) { //child
		exit(0);
	}

	waitpid(pid, &return_status, 0);
	clock_gettime(CLOCK_REALTIME, &ts_end);
	elapsed = diff(ts_start, ts_end);
	printf("\tTime elapsed after %d switches = %ldus\n", ITERATIONS, (elapsed.tv_sec + elapsed.tv_nsec)/1000);

	sem_destroy(sem1);
	sem_destroy(sem2);
}


void *sem_thread1()
{
	int i;
	for(i=0; i<ITERATIONS; i++) {
		sem_wait(&s1);
		sem_post(&s2);
	}
	pthread_exit(NULL);
}

void *sem_thread2()
{
	int i;
	for(i=0; i<ITERATIONS; i++) {
		sem_wait(&s2);
		sem_post(&s1);
	}
	pthread_exit(NULL);
}

void bench_context_thread()
{
	struct timespec elapsed,
			ts_start,
			ts_end;

	unsigned long total = 0;
	int rc;
	pthread_t thread1, thread2;

	/* Bench threads */
	printf("Benchmarking context switches for pthread...\n");

	sem_init(&s1, 0, 1);
	sem_init(&s2, 0, 0);

	/* On commence la mesure ici pour raisons de facilité, mais
	   on devrait retirer à la mesure finale le temps de création
	   d'un tread, si celui-ci n'est pas négligeable. */
	clock_gettime(CLOCK_REALTIME, &ts_start);

	rc = pthread_create(&thread1, NULL, sem_thread1, NULL);
        if(rc) {
                perror("pthread");
                exit(EXIT_FAILURE);
        }

	rc = pthread_create(&thread2, NULL, sem_thread2, NULL);
	if(rc) {
		perror("pthread");
		exit(EXIT_FAILURE);
	}

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	clock_gettime(CLOCK_REALTIME, &ts_end);
	elapsed = diff(ts_start, ts_end);
	total += elapsed.tv_sec + elapsed.tv_nsec;

	printf("\tTime elapsed after %d switches = %ldus\n", ITERATIONS, (elapsed.tv_sec + elapsed.tv_nsec)/1000);
	sem_close(&s1);
	sem_close(&s2);
}

int main(int argc, char *argv[])
{
	bench_fork();

        bench_thread();

	bench_context_fork();

	bench_context_thread();

        return 0;
}
