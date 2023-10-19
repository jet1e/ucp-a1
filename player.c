/*
    FILE: player.c
    AUTHOR: Jet Tue Hung Le
    UNIT: COMP1000
    PURPOSE: Responsible for player movement and car crash logic.
    REFERENCES: UCP Supplementary Videos
    LAST MOD: 14/09/2023
    COMMENTS: none
*/

#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "main.h"

/*
    NAME: movePlayer
    PURPOSE: moves the player on the playable space, maintains crash logic
    IMPORTS: **map, rows, cols, direction
    EXPORTS: nextPos
    REMARKS: none
*/
char movePlayer(char **map, int rows, int cols, char direction)
{
    int currRow, currCol, newRow, newCol;
    int *playerLoc;
    char nextPos;

    playerLoc = (int*)malloc(2*sizeof(int)); /* Allocate memory for the current player location */
    playerLoc = playerLocation(map, playerLoc, rows, cols);
    currRow = playerLoc[0];
    currCol = playerLoc[1];
    nextPos = ' ';

    if(direction == 'w') /* Movement: Player moves up */
    {
        if(currRow != 0) /* Prevents player from moving beyond the bounds */
        {
            newRow = currRow - 1;
            if(((map[currRow][currCol-1] == '>') && (map[currRow][currCol-2] == '*')) || (map[currRow][currCol-1] == '<')) /* Case: *P<.. and ..P<..*/
            {
                nextPos = map[newRow][currCol-1]; /* Ensures player moves down safely with no collisions */
                map[newRow][currCol-1] = 'P';
            }
            else if(((map[currRow][currCol+1] == '<') && (map[currRow][currCol+2] == '*')) || (map[currRow][currCol+1] == '>')) /* Case: ..>P* and ..>P..*/
            {
                nextPos = map[newRow][currCol+1]; /* Ensures player moves down safely with no collisions */
                map[newRow][currCol+1] = 'P';
            }
            else /* Case: Player just moves up normally with no other factors*/
            {
                nextPos = map[newRow][currCol];
                map[newRow][currCol] = 'P';
            }

            /* Ensures the correct tile is placed in the players old location */
            if(currRow % 2 != 0)
            {
                map[currRow][currCol] = '.';
            }
            else
            {
                map[currRow][currCol] = ' ';
            }
        }
    }
    else if(direction == 's') /* Movement: Player moves down */
    {
        if(currRow != rows-1) /* Prevents player from moving beyond the bounds */
        {
            newRow = currRow + 1;
            if(((map[currRow][currCol-1] == '>') && (map[currRow][currCol-2] == '*')) || (map[currRow][currCol-1] == '<')) /* Case: *P<.. and ..P<..*/
            {
                nextPos = map[newRow][currCol-1]; /* Ensures player moves down safely with no collisions */
                map[newRow][currCol-1] = 'P';
            }
            else if(((map[currRow][currCol+1] == '<') && (map[currRow][currCol+2] == '*')) || (map[currRow][currCol+1] == '>')) /* Case: ..>P* and ..>P..*/
            {
                nextPos = map[newRow][currCol+1]; /* Ensures player moves down safely with no collisions */
                map[newRow][currCol+1] = 'P';
            }
            else /* Case: Player just moves down normally with no other factors*/
            {
                nextPos = map[newRow][currCol];
                map[newRow][currCol] = 'P';
            }

            /* Ensures the correct tile is placed in the players old location */
            if(currRow % 2 != 0)
            {
                map[currRow][currCol] = '.';
            }
            else
            {
                map[currRow][currCol] = ' ';
            }
        }
    }
    else if(direction == 'a') /* Movemoent: Player moves left */
    {
        if(currCol != 1) /* Makes sure player does not go out of bounds */
        {
            newCol = currCol - 1; /* Move left = newCol = currCol - 1*/
            nextPos = map[currRow][newCol];
            if(map[currRow][newCol] == '>') /* Case: .>.P. (Crash) */   
            {
                map[currRow][newCol] = 'P';
                map[currRow][currCol] = '.';
            }
            else /* No crash */
            {
                if(map[currRow][currCol+1] == '>') /* Case: Jump*/
                {/* Do nothing */}
                else if(map[currRow][newCol] == '<') /* Case: .P<. (Both moving left)*/
                {
                    map[currRow][currCol-2] = 'P';
                    map[currRow][currCol] = '.';
                    nextPos = '.';
                }
                else /* Case: Standard*/
                {
                    map[currRow][currCol] = map[currRow][newCol];
                    map[currRow][newCol] = 'P';
                }
            }
        }
    }
    else if(direction == 'd') /* Movement: Player moves right */
    {
        if(currCol != cols - 2) /* Makes sure player does not go out of bounds */
        {
            newCol = currCol + 1; /* Move right = newcol = currCol + 1*/
            nextPos = map[currRow][newCol];
            if(map[currRow][newCol] == '<') /* Case: .P.<. (Crash)*/
            {
                map[currRow][newCol] = 'P';
                map[currRow][currCol] = '.';
            }
            else /* No crash */
            {
                if(map[currRow][currCol-1] == '<') /* Case: Jump */
                {/* Do nothing */}
                else if(map[currRow][newCol] == '>') /* Case: .>P. (Both moving right)*/
                {
                    map[currRow][currCol+2] = 'P';
                    map[currRow][currCol] = '.';
                    nextPos = '.';
                }
                else if(map[currRow][newCol] == 'G') /* Scenario: Winning Condition */
                {
                    map[currRow][currCol] = ' ';
                    map[currRow][newCol] = 'P';
                }
                else /* Scenario: Standard*/
                {
                    map[currRow][currCol] = map[currRow][newCol];
                    map[currRow][newCol] = 'P';
                }
            }
        }
    }
    else
    {
        /* Any other input do nothing */
    }

    free(playerLoc); /* Free allocated memory */

    return nextPos; /* Return nextPos to main.c as a condition */
}

/*
    NAME: playerLocation
    PURPOSE: tracks the players location on the map
    IMPORTS: **map, rows, cols, playerLoc
    EXPORTS: playerLoc
    REMARKS: none
*/
int* playerLocation(char **map, int* playerLoc, int rows, int cols)
{
    int i, j;
    /* Iterate through the map */
    for(i=0 ; i<rows; i++)
    {
        for(j=0;j<cols;j++)
        {
            if(map[i][j] == 'P') /* Until Player is found */
            {
                playerLoc[0] = i; /* Load row and column information */
                playerLoc[1] = j;
            }
        }
    }
    return playerLoc; /* Return to the movePlayer() function*/
}