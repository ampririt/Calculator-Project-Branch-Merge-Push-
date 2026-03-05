CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
TARGET  = calc
SRCS    = main.c calc.c

$(TARGET): $(SRCS) calc.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: clean
