# Detect the operating system
ifeq ($(OS),Windows_NT)
    CC = gcc
    EXE = .exe
    RM = del /Q
    DEBUGFLAGS = -g
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CC = gcc
    else ifeq ($(UNAME_S),Darwin)
        CC = clang
    endif
    EXE =
    RM = rm -rf
    DEBUGFLAGS = -g
endif

# Directories
BUILD_DIR = build
SRC_DIR = src
SRC_EXCLUDE_MAIN = $(filter-out main.c, $(SRC_DIR))
INCLUDE_DIR = include
TESTS_DIR = tests
LIB_DIR = lib

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
LIBS = $(wildcard $(LIB_DIR)/*.c)
TESTS = $(wildcard $(TESTS_DIR)/*.c)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

# Project Name
PROJECT_NAME := $(notdir $(realpath $(dir $(lastword $(MAKEFILE_LIST)))))
# Targets
TARGET = $(BUILD_DIR)/$(PROJECT_NAME)$(EXE)
TEST_TARGET = $(BUILD_DIR)/tests$(EXE)

# Compiler Flags
CFLAGS = -Wall -Wextra -Wpedantic -I$(INCLUDE_DIR)

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(SRCS) $(HEADERS) $(LIBS)
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(SRCS)

# Build and run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(SRC_EXCLUDE_MAIN) $(TESTS) $(HEADERS) $(LIBS)
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(TESTS)

# Clean build directory
clean:
	$(RM) $(BUILD_DIR)/*$(EXE)

# Debug target
debug: $(TARGET)
	@echo "Run your debugger (e.g., gdb) with: $(TARGET)"

