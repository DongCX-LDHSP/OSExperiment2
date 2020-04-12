all:myapp

# compiler
CC = gcc

# include location
INCLUDE = .

# options for development
# cflags = -g -Wall -ansi

# options for release
CFLAGS = -O -Wall -ansi

myapp:main.o 2.o 3.o
	$(CC) -o myapp main.o 2.o 3.o

main.o:main.c a.h
	$(CC) -l$(INCLUDE) $(CFLAGS) -c main.c

2.o:2.c a.h b.h
	$(CC) -l$(INCLUDE) $(CFLAGS) -c 2.c

3.o:3.c b.h c.h
	$(CC) -l$(INCLUDE) $(CFLAGS) -c 3.c
