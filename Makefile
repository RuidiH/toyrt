# ───────────────────────────────────────────
# Makefile at your project root
# ───────────────────────────────────────────

# default goal when you just run "make"
all:
	mkdir -p build
	cmake -S . -B build
	cmake --build build
