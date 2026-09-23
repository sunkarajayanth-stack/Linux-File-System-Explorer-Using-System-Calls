CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = explorer

OBJECTS = main.o explorer.o directory.o file_operations.o search.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.c explorer.h directory.h file_operations.h search.h
	$(CC) $(CFLAGS) -c main.c

explorer.o: explorer.c explorer.h
	$(CC) $(CFLAGS) -c explorer.c

directory.o: directory.c directory.h
	$(CC) $(CFLAGS) -c directory.c

file_operations.o: file_operations.c file_operations.h
	$(CC) $(CFLAGS) -c file_operations.c

search.o: search.c search.h
	$(CC) $(CFLAGS) -c search.c

clean:
	rm -f *.o $(TARGET)
