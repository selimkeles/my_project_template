# ============================================================================
#  TemplateProject — GNU Make build system
# ============================================================================
#
#  Targets:
#    make          # build the main executable
#    make build    # alias for the above
#    make test     # build and run the Unity unit tests
#    make test-build  # build the test binary only (for debugging)
#    make run      # run the main executable
#    make bear     # rebuild under bear to emit compile_commands.json (clangd)
#    make clean    # remove all build artifacts
#    make help     # show this help
#
#  Toolchain override (CC/CXX/CFLAGS/...):
#    make CC=clang CXX=clang++
# ============================================================================

# --- Toolchain --------------------------------------------------------------

CC      ?= gcc
CXX     ?= g++
RM      := rm -f

# --- Project layout ---------------------------------------------------------

PROJECT   := TemplateProject
SRC_DIR   := src
TEST_DIR  := tests
UNITY_DIR := $(TEST_DIR)/unity
BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/obj
BIN_DIR   := $(BUILD_DIR)/bin

# --- Flags ------------------------------------------------------------------

CPPFLAGS  := -I$(SRC_DIR) -I$(UNITY_DIR)/src
CFLAGS    ?= -std=c17
CXXFLAGS  ?= -std=c++17
WARNFLAGS := -Wall -Wextra -pedantic
LDFLAGS   :=
LDLIBS    :=

# --- Sources & objects ------------------------------------------------------
# Source files are discovered recursively under src/ (headers stay next to
# sources), so adding a new module requires no Makefile changes. The main
# executable links every source; the test binary links every source except
# main() plus the Unity framework.

SRC_C     := $(shell find $(SRC_DIR) -type f -name '*.c'   2>/dev/null | sort)
SRC_CXX   := $(shell find $(SRC_DIR) -type f -name '*.cpp' 2>/dev/null | sort)

APP_SRCS  := $(SRC_C) $(SRC_CXX)

TEST_SRCS := $(filter-out $(SRC_DIR)/main.c $(SRC_DIR)/main.cpp, $(APP_SRCS)) \
             $(TEST_DIR)/test.c \
             $(UNITY_DIR)/src/unity.c

APP_OBJS  := $(APP_SRCS:%.c=$(OBJ_DIR)/app/%.o)
APP_OBJS  := $(APP_OBJS:%.cpp=$(OBJ_DIR)/app/%.o)
TEST_OBJS := $(TEST_SRCS:%.c=$(OBJ_DIR)/test/%.o)
TEST_OBJS := $(TEST_OBJS:%.cpp=$(OBJ_DIR)/test/%.o)
DEPS      := $(APP_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# C++ requires the C++ driver for linking, whatever the last file is.
LINKER    := $(if $(SRC_CXX),$(CXX),$(CC))

# --- Rules ------------------------------------------------------------------

.PHONY: all build test test-build run bear clean help

all: build

build: $(BIN_DIR)/$(PROJECT)

test-build: $(BIN_DIR)/test_$(PROJECT)

test: test-build
	./$(BIN_DIR)/test_$(PROJECT)

run: $(BIN_DIR)/$(PROJECT)
	./$(BIN_DIR)/$(PROJECT)

# Regenerate compile_commands.json for clangd. A clean rebuild under bear makes
# sure every translation unit is recorded, including the test sources.
bear:
	$(RM) compile_commands.json
	bear --output compile_commands.json -- $(MAKE) clean build test

clean:
	$(RM) -r $(BUILD_DIR)

help:
	@echo 'Available targets:'
	@echo '  make            build the main executable'
	@echo '  make test       build and run the Unity unit tests'
	@echo '  make test-build build the test binary only (for debugging)'
	@echo '  make run        run the main executable'
	@echo '  make bear       rebuild under bear -> compile_commands.json for clangd'
	@echo '  make clean      remove build artifacts'
	@echo 'Overridable variables: CC, CXX, CFLAGS, CXXFLAGS, LDFLAGS, LDLIBS'

# --- Object compilation (auto-dependency tracking: -MMD -MP) ----------------

$(OBJ_DIR)/app/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC)  $(CPPFLAGS) $(CFLAGS)   $(WARNFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR)/app/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(WARNFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR)/test/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC)  $(CPPFLAGS) $(CFLAGS)   $(WARNFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR)/test/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(WARNFLAGS) -MMD -MP -c $< -o $@

# --- Linking -----------------------------------------------------------------

$(BIN_DIR)/$(PROJECT): $(APP_OBJS)
	@mkdir -p $(BIN_DIR)
	$(LINKER) $(APP_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(BIN_DIR)/test_$(PROJECT): $(TEST_OBJS)
	@mkdir -p $(BIN_DIR)
	$(LINKER) $(TEST_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

-include $(DEPS)