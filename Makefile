# Prefer CMake when available (PATH, then Apple Silicon / Intel Homebrew).
CMAKE := $(shell sh -c 'for p in "$$(command -v cmake 2>/dev/null)" /opt/homebrew/bin/cmake /usr/local/bin/cmake; do \
	[ -n "$$p" ] && [ -x "$$p" ] && printf %s "$$p" && exit 0; \
	done')

BUILD_DIR := build
EXE := $(BUILD_DIR)/main

.PHONY: default run build clean

default: run

ifeq ($(strip $(CMAKE)),)
# No cmake found — same flags spirit as CMakeLists.txt (C++17, Release-ish -O3).
CXX ?= c++
CXXFLAGS ?= -std=c++17 -O3 -Wall -Wextra

$(EXE): main.cpp matrix_math.cpp matrix_math.h
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXE) main.cpp matrix_math.cpp

build: $(EXE)

else

$(BUILD_DIR)/Makefile: CMakeLists.txt main.cpp matrix_math.cpp matrix_math.h
	$(CMAKE) -B $(BUILD_DIR) -S . -DCMAKE_BUILD_TYPE=Release

build: $(BUILD_DIR)/Makefile
	$(CMAKE) --build $(BUILD_DIR)

endif

run: build
	$(EXE)

clean:
	rm -rf $(BUILD_DIR)
