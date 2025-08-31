# Simple Makefile for 3DRenderer

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g $(shell pkg-config --cflags sdl2) -I. -Isrc
LDFLAGS := $(shell pkg-config --libs sdl2)

SRC := $(shell find src -name '*.cpp')
BIN := output/main

.PHONY: all run clean debug release asan

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@ $(LDFLAGS)

run: $(BIN)
	./$(BIN)

clean:
	rm -rf output

release: CXXFLAGS := -std=c++17 -O3 -DNDEBUG -Wall -Wextra $(shell pkg-config --cflags sdl2) -I. -Isrc
release: clean all

# Debug build with AddressSanitizer
asan: CXXFLAGS := -std=c++17 -g -O1 -fsanitize=address -fno-omit-frame-pointer -Wall -Wextra $(shell pkg-config --cflags sdl2) -I. -Isrc
asan: clean all

# Alias for explicit debug target (matches README wording)
debug: all
