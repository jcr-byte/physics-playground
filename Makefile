.PHONY: build run clean

build:
	cmake -B build
	cmake --build build

run: build
	./build/physics_playground

clean:
	rm -rf build
