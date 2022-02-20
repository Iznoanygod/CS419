CC = gcc
C_FLAGS = -Wall
C_DEBUG_FLAGS = -g

all:
	$(CC) userlib.c $(C_FLAGS) -c -o userlib.o
	$(CC) domainlib.c $(C_FLAGS) -c -o domainlib.o
	$(CC) typelib.c $(C_FLAGS) -c -o typelib.o
	$(CC) auth.c $(C_FLAGS) -o auth userlib.o domainlib.o typelib.o
debug:
	$(CC) userlib.c $(C_FLAGS) $(C_DEBUG_FLAGS) -c -o userlib.o
	$(CC) domainlib.c $(C_FLAGS) $(C_DEBUG_FLAGS) -c -o domainlib.o
	$(CC) typelib.c $(C_FLAGS) $(C_DEBUG_FLAGS) -c -o typelib.o
	$(CC) auth.c $(C_FLAGS) $(C_DEBUG_FLAGS) -o auth userlib.o domainlib.o
clean:
	rm auth *.o *.txt
