CXX = g++

MACRO_ENABLE_FLAG =

# Add cflags to detect compilation buid warnings
CXXFLAGS = -std=c++17 -Wall -Wunused-variable -Wunused-function -g -I$(INC_DIR) $(MACRO_ENABLE_FLAG)

# Test module enable flag
CXXFLAGS_TEST_BUILD = -DTEST_MODE_ENABLED

# simulation source files
SRC_DIR = src
# simulation build directory
BUILD_DIR = build
# simulation source obj directory
OBJ_DIR = $(BUILD_DIR)/obj
# simulation binary directory
BIN_DIR = install/bin
# simulation include directory
INC_DIR = include
# simulation test result directory
RESULT_DIR = result
