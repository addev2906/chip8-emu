chip8: Main.cpp Chip8.cpp
	g++ -o chip8 Main.cpp Chip8.cpp $(shell pkg-config --cflags --libs sdl3)

clean:
	rm -f chip8
