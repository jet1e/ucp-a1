/*
    FILE: car.c
    AUTHOR: Jet Tue Hung Le
    UNIT: COMP1000
    PURPOSE: Generates cars, movement of cars, car logic.
    REFERENCES: UCP Supplementary Videos
    LAST MOD: 14/09/2023
    COMMENTS: none
*/

#include <stdio.h>
#include <stdlib.h>
#include "car.h"
#include "main.h"
#include "random.h"

/*
    NAME: generateCars
    PURPOSE: generate cars on map, with random locations and random facings
    IMPORTS: rows, cols, **map
    EXPORTS: carLocations
    REMARKS: UCP Supplementary Videos
*/
int* generateCars(int rows, int cols, char **map)
{
    int i, j;
    int* carLocations;
    initRandom();

    carLocations = (int*)malloc(SIZE * sizeof(int)); /* Allocate memory for array of all car locations */

    for(i=0 ; i<rows; i++)
    {
        for(j=0;j<cols;j++)
        {/* Do nothing */}
        if(i%2 != 0)
        {
            /* Generate a random index number within the playable space idx 1 -> cols-2 */
            int randIdx = randomGen(1, cols-2);
            carLocations[i] = randIdx;
            /* Set that location to be a car */
            map[i][randIdx] = randDirection(randIdx,cols); 
        }
    }
    return carLocations;
}

/*
    NAME: randDirection
    PURPOSE: Generate random car facings
    IMPORTS: i, cols
    EXPORTS: car
    REMARKS: UCP Supplementary Videos
*/
char randDirection(char i, int cols)
{
    int x = randomGen(0,1); /* Generate at random a number from 1 and 0 */
    char car = ' ';
    /* Random allocates a car location */
    if(i == 1)
    {
        car = '>';
    }
    else if(i == cols-2)
    {
        car = '<';
    }
    else if(x == 0) /* If car is situated at the left most space, car will be facing right*/
    {
        car = '>';
    }
    else /* If car is situated to the right most space, car will be facing left*/
    {
        car = '<';
    }
    return car; /* Return the car character */
}

/*
    NAME: moveCar
    PURPOSE: Hold the game system, winning conditions, calls functions for game
    IMPORTS: **map, carLocations, rows, cols, direction
    EXPORTS: carLocations
    REMARKS: UCP Supplementary Videos
*/
int* moveCar(char **map, int* carLocations, int rows, int cols, char direction)
{
    int i, j, currCarCol, newCarCol;
    for(i=0 ; i<rows; i++)
    {
        currCarCol = carLocations[i];
        for(j=0;j<cols;j++)
        {/* Do nothing, just iterate through */}

        if(i%2 != 0)
        {
            if(map[i][currCarCol] == '>') /* If the car is > */
            {
                newCarCol = currCarCol + 1;
                if(newCarCol == (cols-2)) /* Case: If moving right and will move to the right most position*/
                {
                    map[i][currCarCol] = map[i][newCarCol];
                    map[i][newCarCol] = '<';
                }
                else /* Case: Just moving right */
                {
                    map[i][currCarCol] = map[i][newCarCol];
                    map[i][newCarCol] = '>';
                }
                carLocations[i] = newCarCol;
            }
            else if(map[i][currCarCol] == '<') /* If the car is < */
            {
                newCarCol = currCarCol - 1;
                if(newCarCol == 1) /* Case: If moving left and will move to the left most position*/
                {
                    map[i][currCarCol] = map[i][newCarCol];
                    map[i][newCarCol] = '>';
                }
                else /* Case: Just moving left*/
                {
                    map[i][currCarCol] = map[i][newCarCol];
                    map[i][newCarCol] = '<';
                }
                carLocations[i] = newCarCol; /* Update the carLocations array with the new location */
            }
        }
    }
    return carLocations;
}