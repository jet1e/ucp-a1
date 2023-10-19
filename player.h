#ifndef PLAYER_H
#define PLAYER_H

char movePlayer(char **map, int rows, int cols, char direction);
int* playerLocation(char **map, int* playerLoc, int rows, int cols);

#endif