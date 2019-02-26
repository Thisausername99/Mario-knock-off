SRC = adventure.c items.c rooms.c
OBJ = adventure.o items.o rooms.o
PROG = mario

$(PROG): $(OBJ)
	gcc $(OBJ) -o $(PROG)

$(OBJ): $(SRC)