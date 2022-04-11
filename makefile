TARGET=myshell
CC=gcc
WARN=-Wall
VERSION=-std=c99
CCFLAGS= $(WARN) $(VERSION) $(PTHREAD)
OBJS= main.o
all: clean $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
 
main.o:
	$(CC) -c $(CCFLAGS) main.c -o main.o
 
clean:
	rm -f *.o myshell