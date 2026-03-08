CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = calendar_manager

all:
	$(CC) $(CFLAGS) -o $(TARGET) main.c calendar_functions.c

clean:
	rm -f $(TARGET)

test: all
	./$(TARGET)