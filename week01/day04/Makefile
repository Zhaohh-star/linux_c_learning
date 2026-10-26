CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET =  greet_app
OBJS = main.o greet.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c  greet.h
	$(CC) $(CFLAGS) -c main.c

greet.o: greet.c greet.h
	$(CC) $(CFLAGS) -c greet.c

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

