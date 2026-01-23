CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = sms

SRCS = src/main.c src/student.c src/input.c src/file.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all run clean