CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lpthread

TARGET = grayscaler
SRCS = grayscaler.c ppm.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean