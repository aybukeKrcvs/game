# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Directories
SRC_DIR = "C:/Users/Aybüke/Dropbox/PC/Desktop/2.1/ceng209/game"
OBJ_DIR = obj
BIN_DIR = bin
SAVE_DIR = saves

# Source files and object files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXEC = $(BIN_DIR)/game

# Default target
all: $(BIN_DIR) $(OBJ_DIR) $(SAVE_DIR) $(EXEC)

# Create executable
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

$(BIN_DIR):
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)

$(SAVE_DIR):
	@if not exist $(SAVE_DIR) mkdir $(SAVE_DIR)

# Clean object and binary files
clean:
	del /Q $(OBJ_DIR)\*.o
	rmdir /S /Q $(OBJ_DIR)
	rmdir /S /Q $(BIN_DIR)

# Run the game
run: $(EXEC)
	$(EXEC)

# Create game save directory
create_saves:
	@if not exist $(SAVE_DIR) mkdir $(SAVE_DIR)