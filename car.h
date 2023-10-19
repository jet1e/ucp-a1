#ifndef CAR_H
#define CAR_H

#define SIZE 999999

char randDirection(char i, int cols);
int* generateCars(int rows, int cols, char **map);
int* moveCar(char **map, int* carLocations, int rows, int cols, char direction);

#endif