# ============================================================================
# Physics Playground Makefile
# ============================================================================
# Cross-platform build system for the Physics Playground project using CMake.
# Supports both Windows and Unix-like systems (Linux/macOS).

# ============================================================================
# PHONY TARGETS
# ============================================================================
# Declare targets that don't create files with the same name
.PHONY: build run clean release installer help

# ============================================================================
# PLATFORM DETECTION AND CONFIGURATION
# ============================================================================
# Detect operating system and set platform-specific variables and commands

ifeq ($(OS),Windows_NT)
    # Windows configuration
    EXE := physics_playground.exe              # Executable name with .exe extension
    PATHSEP := /
    RM_BUILD := if exist build rmdir /s /q build 2>nul || rem  # Remove build dir quietly
    RM_DIST := if exist dist rmdir /s /q dist 2>nul || rem     # Remove dist dir quietly
    MKDIR_BUILD := if not exist build mkdir build             # Create build dir if needed
    MKDIR_DIST := if not exist dist mkdir dist                # Create dist dir if needed
else
    # Unix-like systems (Linux/macOS) configuration
    EXE := physics_playground                  # Executable name without extension
    PATHSEP := /                               # Unix path separator
    RM_BUILD := rm -rf build                   # Force remove build directory
    RM_DIST := rm -rf dist                     # Force remove dist directory
    MKDIR_BUILD := mkdir -p build              # Create build dir with parent dirs
    MKDIR_DIST := mkdir -p dist                # Create dist dir with parent dirs
endif

# ============================================================================
# BUILD TOOLS AND CONFIGURATION
# ============================================================================

# CMake command (assumed to be in PATH on all platforms)
CMAKE := cmake

# Default build configuration (can be overridden: make BUILD_TYPE=Release)
BUILD_TYPE ?= Debug

# Path to Inno Setup compiler for Windows installer creation
# Can be overridden: make ISCC="/custom/path/to/iscc.exe" installer
ISCC ?= "C:\Program Files (x86)\Inno Setup 6\ISCC.exe"

# ============================================================================
# BUILD TARGETS
# ============================================================================

# Display help information about available targets and variables
help:
	@echo "Available targets:"
	@echo "  build       - Build the project in Debug mode"
	@echo "  release     - Build the project in Release mode"
	@echo "  run         - Build and run in Debug mode"
	@echo "  run-release - Build and run in Release mode"
	@echo "  clean       - Remove build and dist directories"
	@echo "  installer   - Build installer (Windows only)"
	@echo "  help        - Show this help message"
	@echo ""
	@echo "Variables:"
	@echo "  BUILD_TYPE  - Build type (Debug/Release), default: Debug"
	@echo "  ISCC        - Path to Inno Setup compiler (Windows only)"

# Build the project using CMake with the specified BUILD_TYPE
# Creates build directory and compiles with parallel processing
build:
	$(CMAKE) -B build -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	$(CMAKE) --build build --config $(BUILD_TYPE) --parallel

# Build the project in Release configuration with optimizations
# Delegates to build target with BUILD_TYPE=Release
release:
	$(MAKE) BUILD_TYPE=Release build

# Build (if needed) and run the executable in Debug mode
# Fails naturally if executable doesn't exist or build fails
run: build
	"build$(PATHSEP)$(BUILD_TYPE)$(PATHSEP)$(EXE)"

# Build and run the executable in Release mode
# Delegates to run target with BUILD_TYPE=Release
run-release:
	$(MAKE) BUILD_TYPE=Release run

# Clean build artifacts and distribution files
# Removes both build/ and dist/ directories
clean:
	$(RM_BUILD)
	$(RM_DIST)

# ============================================================================
# DISTRIBUTION TARGETS
# ============================================================================

# Build Windows installer using Inno Setup Compiler
# Requires: Inno Setup installed, Windows platform
# Creates installer in dist/ directory
installer: release
	$(MKDIR_DIST)
	$(ISCC) installer.iss