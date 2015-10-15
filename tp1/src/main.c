/*
* Author: Geoffrey Bonneville <geoffrey.bonneville@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "colimacon.h"
#include "tests.h"

/*
 * Print a 2D Array
 */
void print2DArray(int *array, int rows, int columns)
{
        int i,
            j;

        printf("\n");
        for (i = 0; i < rows; i++) {
                for (j = 0; j < columns; j++)
                        printf("%4d", array[i * columns + j]);
                printf("\n\n");
        }
        printf("\n");
}

int main(int argc, char *argv[])
{
        int *array = NULL;
        int c;
        int tests_flag = 0;
        int print_flag = 1;
        int rows,
            columns;

        while ((c = getopt(argc, argv, "tp")) != -1)
                switch (c)
                {
                        case 't':
                                tests_flag = 1;
                                break;
                        case 'p':
                                print_flag = 0;
                                break;
                        case '?':
                                if (isprint (optopt))
                                        fprintf (stderr,
                                        "Unknown option `-%c'.\n", optopt);
                                else
                                        fprintf (stderr,
                                        "Unknown option character `\\x%x'.\n",
                                        optopt);
                                        return 1;
                        default:
                                abort ();
        }

        /*** Tests ***/
        if (tests_flag == 1)
                run_all_tests();

        if (argc < 3) {
                printf("Usage: %s [-t -p] rows columns\n", argv[0]);
                return 1; //error
        }

        rows = atoi(argv[optind]);
        columns = atoi(argv[optind+1]);

        if (rows < 1 || columns < 1) {
                printf("Usage: %s [-t -p] rows columns\n", argv[0]);
                return 1; //error
        }

        printf("\nComputing with %d rows and %d columns\n", rows, columns);

        //Build the colimacon
        if (colimacon(&array, rows, columns) == 0)
        {
                printf("FAILED building colimacon");
                return 1; //Error
        }

        if (print_flag == 1)
                print2DArray(array, rows, columns);

        //Do not forget to free the array
        free(array);

        return 1;
}
