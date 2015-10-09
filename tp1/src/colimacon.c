/*
 * Author: Geoffrey Bonneville <geoffrey.bonneville@gmail.com>
 */

#include "colimacon.h"

/*
* Build a 2D array, and fill it like a colimacon.
* return 0 if ok, else return 1
*/
int colimacon(int **array, unsigned int rows, unsigned int columns)
{
        int i;
        int cpt = 1; //Current number used to fill the array
        int cases = rows * columns; //Total number of cases
        int processed = 0; //Number of cases filled

        //Array bounds
        int row_min = 0,
            row_max = rows-1,
            col_min = 0,
            col_max = columns-1;

        int **tab;

        if(rows < 1 || columns < 1)
        return 0; //echec

        /* Memory allocation */
        tab = malloc(rows * sizeof(int *));
        if (tab == NULL) return 0; //Out of memory
        for (i = 0; i < rows; i++)
        {
                tab[i] =  malloc(columns * sizeof(int));
                if (tab[i] == NULL) return 0; //Out of memory
        }

        /* Filling */
        while (processed < cases)
        {
                for (i = col_min; i <= col_max; i++) {
                        tab[row_min][i] = cpt;
                        cpt++;
                        processed++;
                }
                row_min++;

                if (processed >= cases) break;

                for (i = row_min; i <= row_max; i++) {
                        tab[i][col_max] = cpt;
                        cpt++;
                        processed++;
                }
                col_max--;

                if (processed >= cases) break;

                for (i = col_max; i >= col_min; i--) {
                        tab[row_max][i] = cpt;
                        cpt++;
                        processed++;
                }
                row_max--;

                if (processed >= cases) break;

                for (i = row_max; i >= row_min; i--) {
                        tab[i][col_min] = cpt;
                        cpt++;
                        processed++;
                }

                col_min++;
        }

        *array = (int *)tab;

        return 1;
}
