#pragma once
#include <cstdint>

const unsigned int VIDEO_WIDTH = 64;
const unsigned int VIDEO_HEIGHT = 32;

class Chip8{
public:

	Chip8();
	void LoadROM(char const* filename);
	void OP_00E0();
	void OP_Annn();
	void OP_Dxyn();
	void OP_1nnn();
	void Cycle();

	uint8_t registers[16]{};
	uint8_t memory[4096]{};
	uint16_t index{};
	uint16_t pc{};
	uint16_t stack[16]{};
	uint8_t sp{};
	uint8_t delayTimer{};
	uint8_t soundTimer{};
	uint8_t keypad[16]{};
	uint32_t video[64 * 32]{};
	uint16_t opcode;
};
