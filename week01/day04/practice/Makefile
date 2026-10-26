CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = temp_convert
OBJS = main.o temp.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o:main.c temp.h
	$(CC) $(CFLAGS) -c main.c
temp.o:temp.c temp.h
	$(CC) $(CFLAGS) -c temp.c

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)



