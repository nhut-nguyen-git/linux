# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Target executable name
TARGET = example_program

# Source file
SRC = main.c

# Object file
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Link object file into executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile source into object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean generated files
clean:
	rm -f $(OBJ) $(TARGET)