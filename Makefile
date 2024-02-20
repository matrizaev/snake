PREFIX ?= 
BUILD_DIR = build
SRC_DIR = src
BIN_DIR = bin
TARGET = snake
SRCS = $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJS = $(subst $(SRC_DIR)/, $(BUILD_DIR)/, $(SRCS:.c=.o))
TEST_SRCS = $(wildcard tests/*_tests.c)
TEST_OBJS = $(filter-out $(addsuffix .o, $(BUILD_DIR)/$(TARGET)), $(OBJS))
TESTS = $(patsubst %.c,%,$(TEST_SRCS))
CFLAGS_PROD = -std=c17 -O3 -I$(SRC_DIR) $(OPTGLAGS) $(CFLAGS_DEPS)  -D_DEFAULT_SOURCE -DNDEBUG
CFLAGS_DEV = -std=c17 -g -O0 -I$(SRC_DIR) $(OPTGLAGS) $(CFLAGS_DEPS) -D_DEFAULT_SOURCE
LDFLAGS = -lncurses

.PHONY: dev all clean test

all: CFLAGS = $(CFLAGS_PROD)
all: $(TARGET)
dev: CFLAGS = $(CFLAGS_DEV) -Wall -Wextra -Wshadow
dev: $(TARGET)
$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(RELEASE_FLAGS) -o $(BIN_DIR)/$(TARGET)

test: CFLAGS = $(CFLAGS_DEV)
test: $(BUILD_DIR) $(TEST_OBJS) $(TESTS)
	sh ./tests/runtests.sh

$(TESTS): CFLAGS += $(TEST_OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

build:
	@mkdir -p build
	@mkdir -p bin
clean:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)
	rm -f tests/tests.log
	rm -f $(TESTS)
	rm -f $(TEST_OBJS)
