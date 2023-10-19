/*
    FILE: random.c
    AUTHOR: Jet Tue Hung Le
    UNIT: COMP1000
    PURPOSE: Randomly generates a number
    REFERENCES: UCP Supplementary Video- Random Number Generator
    LAST MOD: 14/09/2023
    COMMENTS: Responsible for deciding the initial facing and locations of cars
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "random.h"
#include "main.h"

/*
    NAME: initRandom
    PURPOSE: 
    IMPORTS: none
    EXPORTS: none
    REMARKS: UCP Supplementary Videos
*/
void initRandom()
{
    srand(time(NULL));
}

/*
    NAME: initRandom
    PURPOSE: Randomly generates a number. Where lower will equal lowest playable space (col=1) and upper is highest (col-2). 
             Also used to decide the direction of the car, range is [0,1]
    IMPORTS: lower, upper
    EXPORTS: n
    REMARKS: UCP Supplementary Videos
*/
int randomGen(int lower, int upper)
{
    int n = -1;
    if(lower <= upper)
    {
        n = (rand() % (upper - lower +1)) + lower;
    }
    return n;
}