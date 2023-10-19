CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = main.o map.o car.o random.o player.o
EXEC = traffic

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c main.h car.h map.h player.h
	$(CC) -c main.c $(CFLAGS)

map.o : main.h map.h map.c car.h
	$(CC) -c map.c $(CFLAGS)

car.o: car.h main.h car.c random.h
	$(CC) -c car.c $(CFLAGS)

random.o: random.h main.h random.c
	$(CC) -c random.c $(CFLAGS)

player.o: player.h player.c main.h
	$(CC) -c player.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)