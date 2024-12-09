# Compiler and flags
CXX := g++
CXXFLAGS := -g -Wall -std=c++14

# Directories
SRC_PATH := ./src
ENC_PATH := ./src/encoder
DEC_PATH := ./src/decoder
BUILD_PATH := ./obj
BUILD_SUBDIRS := ./obj/encoder ./obj/decoder

# Source files
SRC_ENC := $(SRC_PATH)/utilities.cpp $(wildcard $(ENC_PATH)/*.cpp)
SRC_DEC := $(SRC_PATH)/utilities.cpp $(wildcard $(DEC_PATH)/*.cpp)

# Object files
OBJ_ENC := $(patsubst $(SRC_PATH)/%.cpp,$(BUILD_PATH)/%.o,$(SRC_ENC))
OBJ_DEC := $(patsubst $(SRC_PATH)/%.cpp,$(BUILD_PATH)/%.o,$(SRC_DEC))

# Target executables
TARGET_ENC := ./rds_encoder
TARGET_DEC := ./rds_decoder

# Default target
all: $(TARGET_ENC) $(TARGET_DEC)

# Rule to create the object directories if they don't exist
$(BUILD_PATH):
	mkdir -p $@

$(BUILD_SUBDIRS):
	mkdir -p $@

# Link the object files to create the executables
$(TARGET_ENC): $(OBJ_ENC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET_DEC): $(OBJ_DEC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp | $(BUILD_PATH) $(BUILD_SUBDIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ_ENC) $(OBJ_DEC) $(TARGET_ENC) $(TARGET_DEC)

.PHONY: all clean