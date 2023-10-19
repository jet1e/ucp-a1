/*
    FILE: map.c
    AUTHOR: Jet Tue Hung Le
    UNIT: COMP1000
    PURPOSE: Creates the playable map area, and displays it.
    REFERENCES: UCP Supplementary Videos
    LAST MOD: 14/09/2023
    COMMENTS: none
*/

#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "map.h"
#include "car.h"

/*
    NAME: createMap
    PURPOSE: Creates the map with border, road, goal and initial player location
    IMPORTS: rows, cols
    EXPORTS: map
    REMARKS: none
*/
char** createMap(int rows, int cols)
{
    int i, j, k;
    char **map;

    map = (char**)malloc(rows * sizeof(char*)); /* Allocate memory for 2D array map */
    for(k = 0; k < rows; k++) /* Create 2D array for map: Array of pointers to chars */
    {
        map[k] = (char*)malloc(cols * sizeof(char));
    }

    /* 
    NOTE: In main.h I have +2 increases the column number to place border at 1st idx and last
    Therefore, cols-1 = a border, and cols-2 = last playable space
    */

    /* Iterate through the 2D array */
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if((j == 0) || (j == cols - 1)) /* Creates the border: Column 0 and Column cols-1 is the border */
            {
                map[i][j] = '*';
            }
            else
            {
                /* Creates the playable space */
                if((i == 0) && (j == 1)) /* Initial player position */
                {
                    map[i][j] = 'P';
                }
                else if((i == rows -1) && (j == cols - 2)) /* Goal position */
                {
                    map[i][j] = 'G';
                }
                else if(i%2 != 0) /* Every even row of the playable space is the road */
                {
                    map[i][j] = '.';
                }
                else /* Every odd row of the playable space is the path */
                {
                    map[i][j] = ' ';
                }
            }
        }
    }
   return map; /* Returned to main.c */
}

/*
    NAME: border
    PURPOSE: creates the top and bottom border
    IMPORTS: cols
    EXPORTS: none
    REMARKS: none
*/
void border(int cols)
{
    int i;
    /* Creates the top and bottom borders */
    for(i = 0; i < cols; i++)
    {
        printf("*");
    }

    printf("\n");
}

/*
    NAME: displayMap
    PURPOSE: displays map to the function
    IMPORTS: rows, cols, **map
    EXPORTS: none
    REMARKS: none
*/
void displayMap(int rows, int cols, char **map)
{
    int i, j;
    border(cols); /* Top border */
    for(i = 0; i < rows; i++) /* Iterate through the 2D array */
    {
        for(j = 0; j < cols; j++)
        {
            printf("%c", map[i][j]); /* Display each element of the array to terminal */
        }
        printf("\n"); /* Breaks up each row onto a new line */
    }
    border(cols); /* Bottom border */
    controlDesc(); /* Controls */
}

/*
    NAME: controlDesc
    PURPOSE: prints the controls, and what they do
    IMPORTS: none
    EXPORTS: none
    REMARKS: none
*/
void controlDesc()
{
    printf("Press [w] to move up\n");
    printf("Press [s] to move down\n");
    printf("Press [a] to move left\n");
    printf("Press [d] to move right\n");
}
