CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = exp2

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET)

clean:
	rm -f $(TARGET)
