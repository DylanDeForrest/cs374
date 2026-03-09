CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = speed

.PHONY: all clean

all: $(TARGET)

$(TARGET): speed.c
	$(CC) $(CFLAGS) -o $(TARGET) speed.c

clean:
	rm -f $(TARGET)