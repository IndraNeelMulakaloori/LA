# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=gnu++17 -Wall

# Directories
INCLUDE_DIR = include
SRC_DIR = src
MAIN_DIR = main
BUILD_DIR = build

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
MAIN_FILE = $(MAIN_DIR)/main.cpp
MAIN_OBJ_FILE = $(BUILD_DIR)/main.o

# Executable
EXECUTABLE = $(BUILD_DIR)/output

# Default target
all: $(EXECUTABLE)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/main.o: $(MAIN_FILE) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Build executable
$(EXECUTABLE): $(OBJ_FILES) $(MAIN_OBJ_FILE)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean