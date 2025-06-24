# ───────────────────────────────────────────
# Makefile for running my project
# ───────────────────────────────────────────

.PHONY: all build test clean

# 1. Default goal: running `make` invokes `all`
all: build

# 2. Build rule: configure & compile
build:
	mkdir -p build
	cmake -S . -B build
	cmake --build build

# 3. Test rule: depends on build, then runs ctest
test: build
	@echo "=== Running unit tests ==="
	cd build && ctest --output-on-failure

# 4. Clean rule: removes build artifacts
clean:
	rm -rf build