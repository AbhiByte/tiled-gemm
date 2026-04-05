# Prefer CMake when available (PATH, then Apple Silicon / Intel Homebrew).
CMAKE := $(shell sh -c 'for p in "$$(command -v cmake 2>/dev/null)" /opt/homebrew/bin/cmake /usr/local/bin/cmake; do \
	[ -n "$$p" ] && [ -x "$$p" ] && printf %s "$$p" && exit 0; \
	done')

BUILD_DIR := build
EXE := $(BUILD_DIR)/main
VERIFY := $(BUILD_DIR)/verify_gemm

.PHONY: default run build clean check check-cmake

default: run

ifeq ($(strip $(CMAKE)),)
# No cmake found — same flags spirit as CMakeLists.txt (C++17, Release-ish -O3).
CXX ?= c++
CXXFLAGS ?= -std=c++17 -O3 -Wall -Wextra

$(VERIFY): verify_gemm.cpp matrix_math.cpp matrix_math.h
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(VERIFY) verify_gemm.cpp matrix_math.cpp

check: $(VERIFY)
	$(VERIFY)

$(EXE): main.cpp matrix_math.cpp matrix_math.h $(VERIFY)
	$(VERIFY)
	$(CXX) $(CXXFLAGS) -o $(EXE) main.cpp matrix_math.cpp

build: $(EXE)

run: check $(EXE)
	$(EXE)

else

$(BUILD_DIR)/Makefile: CMakeLists.txt main.cpp matrix_math.cpp matrix_math.h verify_gemm.cpp
	$(CMAKE) -B $(BUILD_DIR) -S . -DCMAKE_BUILD_TYPE=Release

check-cmake: $(BUILD_DIR)/Makefile
	$(CMAKE) --build $(BUILD_DIR) --target verify_gemm
	$(VERIFY)

build: $(BUILD_DIR)/Makefile
	$(CMAKE) --build $(BUILD_DIR)

run: check-cmake build
	$(EXE)

endif

clean:
	rm -rf $(BUILD_DIR)
