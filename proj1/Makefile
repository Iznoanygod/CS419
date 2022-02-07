CC = gcc
C_FLAGS = -Wall
C_DEBUG_FLAGS = -g

all:
	$(CC) userlib.c $(C_FLAGS) -c -o userlib.o
	$(CC) auth.c $(C_FLAGS) -o auth userlib.o
debug:
	$(CC) $(C_FLAGS) $(C_DEBUG_FLAGS) -c -o userlib.o
	$(CC) $(C_FLAGS) $(C_DEBUG_FLAGS) -o auth userlib.o
clean:
	rm auth *.o *.txt
