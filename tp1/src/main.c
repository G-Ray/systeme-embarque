/*
* Author: Geoffrey Bonneville <geoffrey.bonneville@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include "colimacon.h"
#include "tests.h"

/*
* Print a 2D Array
*/
void print2DArray(int **array, int rows, int columns)
{
        int i,
            j;

        printf("\n");
        for (i = 0; i < rows; i++) {
                for (j = 0; j < columns; j++)
                printf("%4d", array[i][j]);
                printf("\n\n");
        }
        printf("\n");
}

/*
* Destroy a 2D Array
*/
void destroy2DArray(int **array, int rows, int columns)
{
        int i;

        for (i = 0; i < rows; i++)
        {
                free(array[i]);
        }
        free(array);
}

int main(int argc, char *argv[])
{
        int *array = NULL;
        int rows,
            columns;

        if (argc != 3)
        {
                printf("Usage: %s rows columns\n", argv[0]);
                return 1; //error
        }

        /*** Tests ***/
        run_all_tests();
        /*************/

        //TODO: Verify args are int
        rows = atoi(argv[1]);
        columns = atoi(argv[2]);

        if(rows < 1 || columns < 1) {

        }

        printf("Computing with %d rows and %d columns\n", rows, columns);

        //TODO: error handlings
        if (colimacon(&array, rows, columns) == 0)
        {
                printf("FAILED building colimacon");
                return 1; //Error
        }

        //array is now a 2D array
        int **tab = (int **) array;

        print2DArray(tab, rows, columns);
        destroy2DArray(tab, rows, columns);
        //should fail after destroy2DArray
        //print2DArray(tab, rows, columns);

        return 1;
}
