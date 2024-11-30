# Compiler and flags
CXX := g++
CXXFLAGS := -g -Wall -std=c++14

# Directories
SRC_PATH := ./src
ENC_PATH := ./src/encoder
BUILD_PATH := ./build

# Source files
SRC := $(SRC_PATH)/utilities.cpp $(wildcard $(ENC_PATH)/*.cpp)

# Object files
#OBJ := $(SRC:.cpp=.o)
OBJ := $(patsubst $(SRC_PATH)/%.cpp,$(BUILD_PATH)/%.o,$(SRC))

# Target executable
TARGET := ./rds_encoder

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean