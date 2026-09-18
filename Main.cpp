#include "Chip8.hpp"
#include <cstdio>

int main(int argc, char** argv){
	if (argc < 2){
		printf("Usage: %s <ROM file>\n", argv[0]);
		return 1;
	}

	Chip8 chip8;
	chip8.LoadROM(argv[1]);

	return 0;
}
