#ifndef MAIN_H
#define MAIN_H

#define ROWS (atoi(argv[1]))
#define COLS (atoi(argv[2]) + 2) 
/* 
    +2 increases the column size to place boarder at 1st idx and last
    Therefore, cols-1 = a border, and cols-2 = last playable space
*/

void newSleep(float sec);
void disableBuffer();
void enableBuffer();

#endif
