/*
    FILE: main.c
    AUTHOR: Jet Tue Hung Le
    UNIT: COMP1000
    PURPOSE: Create a game system, call relevant files to do so, include argument logic.
    REFERENCES: UCP Supplementary Videos
    LAST MOD: 14/09/2023
    COMMENTS: none
*/

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include "main.h"
#include "car.h"
#include "map.h"
#include "player.h"

/*
    NAME: main
    PURPOSE: Hold the game system, winning conditions, calls functions for game
    IMPORTS: argc, *argv[]
    EXPORTS: none
    REMARKS: UCP Supplementary Videos
*/
int main(int argc, char *argv[])
{
    char** map;
    int* carLocations;
    char direction, condition;
    int i;

    condition = '.';

    if((argc != 3)) /* Case: Arguments is less than 3 */
    {
        printf("Usage: %s <rows> <cols>\n", argv[0]);
    }
    else if(COLS < 5) /* Case: Column number is below 5*/
    {
        printf("Error cols < 5: Minimum number of columns is 5.\n");
    }
    else if(ROWS < 3) /* Case: Row number is below 3 */
    {
        printf("Error rows < 3: Minimum number of rows is 3.\n");
    }
    else if(ROWS % 2 == 0) /* Case: Rows is not odd */
    {
        printf("Error: Row is not odd.\n");
    }
    else
    {
        map = createMap(ROWS, COLS); /* Calls functions to create the playable map */
        system("clear"); /* Terminal sleeps */
        carLocations = generateCars(ROWS, COLS, map); /* Cars are generated at random, return an array of all the car locations */
        displayMap(ROWS, COLS, map); /* Displays the map to terminal */

        while((condition != /* Source: UCP Supplementary Videos */'>') && (condition != '<') && (condition != 'G')) /* While not a terminating condition win/loss */
        {
            disableBuffer();
            scanf("%c", &direction); /* User input w/a/s/d */
            if((direction == 'w') || (direction == 'a') || (direction == 's') || (direction == 'd')) /* If a valid input */
            {
                carLocations = moveCar(map, carLocations, ROWS, COLS, direction); /* Move cars and update the location array */
                condition = movePlayer(map, ROWS, COLS, direction); /* Moves player location, returns a condition */
                system("clear");
                displayMap(ROWS, COLS, map); /* Display map */
                enableBuffer();
                if((condition == '>') || (condition == '<')) /* Case: Condition is a car, crash has happened, player loses, terminates out of while */
                {
                    printf("You lose!\n");
                }
                else if(condition == 'G') /* Case: Condition is the goal, player wins, end of game, terminates out of while loop*/
                {
                    printf("You win!\n");
                }
                else 
                {/* No terminating condition. Do nothing */}
            } /* Else do nothing, an re-loop for the input */
        }

        /* Free allocated (malloc'd) memory */
        for (i = 0; i < ROWS; i++) /* For the map */
        {
            free(map[i]);
        }
        free(map);
        free(carLocations); /* For the array of car locations */
    }

    return 0;
}
/*
    NAME: newSleep
    PURPOSE: sleeps terminal
    IMPORTS: sec
    EXPORTS: none
    REMARKS: UCP Supplementary Videos
*/
void newSleep(float sec)
{
    struct timespec ts;
    ts.tv_sec = (int) sec;
    ts.tv_nsec = (sec - ((int) sec)) * 1000000000;
    nanosleep(&ts, NULL);
}

/*
    NAME: disableBuffer
    PURPOSE: disables input buffer
    IMPORTS: none
    EXPORTS: none
    REMARKS: UCP Supplementary Videos
*/
void disableBuffer()
{
    struct termios mode;
    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

/*
    NAME: enableBuffer
    PURPOSE: enables input buffer
    IMPORTS: none
    EXPORTS: none
    REMARKS: UCP Supplementary Videos
*/
void enableBuffer()
{
    struct termios mode;
    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}