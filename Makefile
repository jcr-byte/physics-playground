.PHONY: build run clean

# Detect cmake path (works on Windows)
CMAKE := $(shell where cmake 2>nul || echo cmake)

build:
	$(CMAKE) -B build
	$(CMAKE) --build build

run: build
	.\build\Debug\physics_playground.exe

clean:
	if exist build rmdir /s /q build