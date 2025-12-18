.PHONY: build run clean

# Detect OS and set platform-specific variables
ifeq ($(OS),Windows_NT)
    EXE := physics_playground.exe
    # Remove build directory quietly; '|| rem' swallows error if directory doesn't exist
    RM := rmdir /s /q build 2>nul || rem
    MKDIR := if not exist build mkdir build
else
    EXE := physics_playground
    RM := rm -rf build
    MKDIR := mkdir -p build
endif

# Use cmake (works cross-platform)
CMAKE := cmake

build:
	$(CMAKE) -B build
	$(CMAKE) --build build --parallel

run: build
	./build/$(EXE)

clean:
	$(RM)