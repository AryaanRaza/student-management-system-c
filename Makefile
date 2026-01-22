CFLAGS = -Wall -Wextra -std=c11
TARGET = sms
SRCS = main.c student.c input.c file.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Move the delete command down here!
clean:
	rm -f *.o *.exe