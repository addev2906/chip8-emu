#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "headers/Chip8.hpp"
#include "headers/Platform.hpp"

void saveProgram(Chip8& chip8, int start, int count){
    std::ofstream output("program.txt");
    if(output.is_open()){
        for (int i = start; i < start + count; ++i)
                {
                    // Replaces printf("%03X: %02X\n", i, chip8.memory[i]);
                    output << std::uppercase << std::hex
                           << std::setfill('0') << std::setw(3) << i << ": "
                           << std::setfill('0') << std::setw(2) << static_cast<int>(chip8.memory[i]) << "\n";
                }
                output.close(); // Good practice to close the file explicitly
    }
}
int main(int argc, char** argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
		return 1;
	}

	int videoScale = std::stoi(argv[1]);
	int cycleDelay = std::stoi(argv[2]);
	char const* romFilename = argv[3];

	Platform platform("CHIP-8 Emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

	Chip8 chip8;
	chip8.LoadROM(romFilename);
	saveProgram(chip8, 0x200,3583);

	int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;

	auto lastCycleTime = std::chrono::high_resolution_clock::now();
	auto lastTimerTime = std::chrono::high_resolution_clock::now();
	bool quit = false;

	while (!quit)
	{
		quit = platform.ProcessInput(chip8.keypad);
		platform.ProcessAudio(chip8.soundTimer);

		auto currentTime = std::chrono::high_resolution_clock::now();

		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();
		if (dt > cycleDelay)
		{
			lastCycleTime = currentTime;
			chip8.Cycle();
			platform.Update(chip8.video, videoPitch);
		}

		float timerDt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastTimerTime).count();
		if (timerDt > 1000.0f / 60.0f)   // ~16.67ms, true 60Hz
		{
			lastTimerTime = currentTime;
			if (chip8.delayTimer > 0) chip8.delayTimer--;
			if (chip8.soundTimer > 0) chip8.soundTimer--;
		}
	}

	return 0;
}
