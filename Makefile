CC      := gcc
AR      := ar
ARFLAGS := rcs

SRC     := $(wildcard src/*.c)

BUILD_DIR := build
OBJ     := $(SRC:src/%.c=$(BUILD_DIR)/%.o)
LIB     := libvfcutils.a

# -------- Configuration --------

CONFIG ?= release

CFLAGS_COMMON := -Wall -Wextra -std=c11 -Iinclude

ifeq ($(CONFIG),debug)
    CFLAGS := $(CFLAGS_COMMON) \
              -g \
              -O0 \
              -fsanitize=address \
              -fstack-protector-strong
else ifeq ($(CONFIG),release)
    CFLAGS := $(CFLAGS_COMMON) \
              -O3 \
              -DNDEBUG
else
    $(error Unknown CONFIG=$(CONFIG))
endif

# -------- Rules --------

.PHONY: all clean debug release

all: $(LIB)

debug:
	$(MAKE) CONFIG=debug

release:
	$(MAKE) CONFIG=release

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf build $(LIB)
