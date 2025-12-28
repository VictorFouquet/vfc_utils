CC      := gcc
CFLAGS  := -g -Wall -Wextra -std=c11 \
           -fsanitize=address \
           -fstack-protector-strong \
           -Iinclude
AR      := ar
ARFLAGS := rcs
SRC     := $(wildcard src/*.c)
OBJ     := $(SRC:src/%.c=build/%.o)
LIB     := libutils.a

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build $(LIB)