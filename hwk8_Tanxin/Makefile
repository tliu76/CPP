# Compiler
CC = gcc

# Flags: -Wall enables warnings, -g adds debug info
CFLAGS = -Wall -g

# Object files
OBJS = main.o graph.o set.o list.o

# Output binary
TARGET = maze

# Default target
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile .c files to .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(TARGET) $(OBJS)
