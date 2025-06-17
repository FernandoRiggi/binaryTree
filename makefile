CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -g

OBJS = main.o binary_tree.o

EXEC = binary_tree_simulator

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

main.o: main.c binary_tree.h
	$(CC) $(CFLAGS) -c main.c

binary_tree.o: binary_tree.c binary_tree.h
	$(CC) $(CFLAGS) -c binary_tree.c

clean:
	rm -f $(OBJS) $(EXEC)