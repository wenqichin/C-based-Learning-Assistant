# Makefile for Learning Assistant for Programming Education

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = learning_assistant
SOURCES = menu.c learner_profile.c file_operations.c content_management.c interaction_logging.c recommendation_engine.c feedback_reports.c
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
