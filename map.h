#ifndef MAP_H
#define MAP_H

#define FIRST rows
#define LAST (cols-1)

void border(int cols);
void displayMap(int rows, int cols, char **map);
char** createMap(int rows, int cols);
void controlDesc();

#endif
