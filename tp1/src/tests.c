/*
 * Author: Geoffrey Bonneville <geoffrey.bonneville@gmail.com>
 */

#include "tests.h"
#include "colimacon.h"

static int test1[3][4] = {
        {1,  2,  3,  4},
        {10, 11, 12, 5},
        {9,  8,  7,  6}
};

static int test2[6][6] = {
        {1,  2,  3,  4,  5,  6},
        {20, 21, 22, 23, 24, 7},
        {19, 32, 33, 34, 25, 8},
        {18, 31, 36, 35, 26, 9},
        {17, 30, 29, 28, 27, 10},
        {16, 15, 14, 13, 12, 11}
};

static int test3[4][3] = {
        { 1,  2, 3},
        {10, 11, 4},
        { 9, 12, 5},
        { 8,  7, 6}
};

static int test4[5][2] = {
        { 1, 2},
        {10, 3},
        { 9, 4},
        { 8, 5},
        { 7, 6}
};

static int test5[1][1] = {
        {1}
};

int compare_2D_arrays(const int rows, const int columns,
                        int testArray[rows][columns], int *array)
{
        int i, j;

        for (i = 0; i < rows; i++) {
                for (j = 0; j < columns; j++) {
                        if (testArray[i][j] != array[i * columns + j]) {
                                printf("Test failed!\n");
                                return 1; //failed
                        }
                }
        }

        printf("Test passed!\n");

        return 0;
}

/*
* return 0 if ok, else return 1
*/
int run_all_tests()
{
        int *array = NULL;
        int rows = 3;
        int columns = 4;

        /* Test 1 */
        printf("Running test 1... ");
        colimacon(&array, rows, columns);
        compare_2D_arrays(rows, columns, test1, array);

        /* Test 2 */
        printf("Running test 2... ");
        rows = 6;
        columns = 6;
        colimacon(&array, rows, columns);
        compare_2D_arrays(rows, columns, test2, array);

        /* Test 3 */
        printf("Running test 3... ");
        rows = 4;
        columns = 3;
        colimacon(&array, rows, columns);
        compare_2D_arrays(rows, columns, test3, array);

        /* Test 4 */
        printf("Running test 4... ");
        rows = 5;
        columns = 2;
        colimacon(&array, rows, columns);
        compare_2D_arrays(rows, columns, test4, array);

        /* Test 5 */
        printf("Running test 5... ");
        rows = 1;
        columns = 1;
        colimacon(&array, rows, columns);
        compare_2D_arrays(rows, columns, test5, array);

        return 0;
}
