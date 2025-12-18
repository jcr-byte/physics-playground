.PHONY: build run clean release installer

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

release:
	$(CMAKE) -B build -DCMAKE_BUILD_TYPE=Release
	$(CMAKE) --build build --config Release --parallel

run: build
	./build/Debug/$(EXE)

run-release: release
	./build/Release/$(EXE)

clean:
	$(RM)

# Build Windows installer (requires Inno Setup installed)
installer: release
	@if not exist dist mkdir dist
	"C:\Program Files (x86)\Inno Setup 6\ISCC.exe" installer.iss