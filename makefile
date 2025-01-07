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
INCLUDE_DIR = include
TESTS_DIR = tests
LIB_DIR = lib

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
LIBS = $(wildcard $(LIB_DIR)/*.c)
TESTS = $(wildcard $(TESTS_DIR)/*.c)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

# Targets
TARGET = $(BUILD_DIR)/my_project$(EXE)
TEST_TARGET = $(BUILD_DIR)/tests$(EXE)

# Compiler Flags
CFLAGS = -Wall -Wextra -Wpedantic -I$(INCLUDE_DIR)

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(SRCS) $(HEADERS) $(LIBS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(SRCS)

# Build and run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TESTS) $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(TESTS)

# Clean build directory
clean:
	$(RM) $(BUILD_DIR)/*$(EXE)

# Debug target
debug: $(TARGET)
	@echo "Run your debugger (e.g., gdb) with: $(TARGET)"

