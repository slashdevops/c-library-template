.DELETE_ON_ERROR: clean

# Where to find tools
TEST_APP = test_linkedlist
TARGET_LIB = linkedlistlib.so

CC_MACOS = "/opt/homebrew/bin/gcc-13"
CC_LINUX = "/usr/bin/gcc"

AR_MACOS = "/opt/homebrew/bin/gcc-ar-13"
AR_LINUX = "/usr/bin/ar"

MEMCHECK_MACOS = "/usr/bin/leaks"
MEMCHECK_LINUX = "/usr/bin/valgrind"

# Determine OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	MEMCHECK = $(MEMCHECK_MACOS)
	CC = $(CC_MACOS)
	AR = $(AR_MACOS)
endif
ifeq ($(UNAME_S),Linux)
	MEMCHECK = $(MEMCHECK_LINUX)
	CC = $(CC_LINUX)
	AR = $(AR_LINUX)
endif

# Check if OS is supported
ifneq ($(UNAME_S),Darwin)
	ifneq ($(UNAME_S),Linux)
	$(error "Unsupported OS")
	endif
endif

# Check if executables are in PATH
EXECUTABLES = $(CC) $(AR) $(MEMCHECK)
K := $(foreach exec,$(EXECUTABLES),\
  $(if $(shell which $(exec)),some string,$(error "No $(exec) in PATH)))

# Compiler and linker flags
CFLAGS = -Wall -Wextra -Werror -Wunused -O2 -g -std=c2x -pedantic # Compiler flags
LDFLAGS = -shared # Linker flags (shared library)  (change to -static for static library)

SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib

TEST_SRC_DIR := tests
TEST_OBJ_DIR := obj
BUILD_DIR := build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_FILES = $(wildcard $(TEST_SRC_DIR)/*.c)
TEST_OBJS = $(TEST_FILES:$(TEST_SRC_DIR)/%.c=$(TEST_OBJ_DIR)/%.o)

INCLUDE_DIRS = -Iinclude

# Targets
##@ Default target
.PHONY: all
all: clean build ## Clean and build the library

##@ Build commands
.PHONY: clean build
build: $(TARGET_LIB) ## Clean and build the library

$(TARGET_LIB): $(OBJ_FILES) | $(LIB_DIR)
	$(CC) $(LDFLAGS) -o $(LIB_DIR)/$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c -o $@ $<

$(TEST_APP): $(TEST_OBJS) $(LIB_DIR)/$(TARGET_LIB) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $(BUILD_DIR)/$@ $^

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c -o $@ $<

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

##@ Test commands
.PHONY: test
test: clean build $(TEST_APP) ## Run tests
	@echo "Running tests..."
	./$(BUILD_DIR)/$(TEST_APP)

.PHONY: memcheck
memcheck: test ## Run tests and check for memory leaks
	@echo "Running tests with valgrind..."
	leaks --atExit -- ./$(BUILD_DIR)/$(TEST_APP)

##@ Clean commands
.PHONY: clean
clean: ## Clean built artifacts
	@rm -rf $(BUILD_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIB_DIR)

##@ Help commands
.PHONY: help
help: ## Display this help
	@awk 'BEGIN {FS = ":.*##";                                             \
		printf "Usage: make \033[36m<target>\033[0m\n"} /^[a-zA-Z_-]+:.*?##/ \
		{ printf "  \033[36m%-10s\033[0m %s\n", $$1, $$2 } /^##@/            \
		{ printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } '                  \
		$(MAKEFILE_LIST)