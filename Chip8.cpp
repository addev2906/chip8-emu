#include "Chip8.hpp"
#include <cstdint>
#include <fstream>
#include <cstring>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8(){
	pc = START_ADDRESS;
	for(int i=0;i<80;i++){
	    memory[FONTSET_START_ADDRESS+i] = fontset[i];
	}
}

void Chip8::LoadROM(char const* filename){
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open()){
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		for (long i = 0; i < size; ++i){
			memory[START_ADDRESS + i] = buffer[i];
		}

		delete[] buffer;
	}
}

void Chip8::OP_00E0(){
    std::memset(video,0,sizeof(video));
}

void Chip8::OP_Annn(){
    uint16_t address = opcode & 0x0FFF;
    index = address;
}
void Chip8::OP_Dxyn(){
    uint8_t Vx =  (opcode & 0x0F00) >> 8u;
    uint8_t Vy =  (opcode & 0x00F0) >> 8u;
    uint8_t height = opcode & 0x000F;

    uint8_t xpos = registers[Vx]%VIDEO_WIDTH;
    uint8_t ypos = registers[Vy]%VIDEO_HEIGHT;

    registers[0xF] = 0;

    for(uint8_t row=0;row<height;row++){
        uint8_t spriteByte = memory[index+row];
        for(int col=0;col<8;col++){
            uint8_t spritePixel = spriteByte & (0x0800 >> col);
            uint32_t* screenPixel = &video[(ypos+row)*VIDEO_WIDTH+(xpos+col)];

            if(spritePixel){
                if(*screenPixel==0xFFFFFFFF){
                    registers[0xF] = 1;
                }
                *screenPixel ^= 0xFFFFFFFF;
            }
        }
    }
}

void Chip8::OP_1nnn(){
    uint16_t address = (opcode & 0x0FFFu);
    pc=address;
}
