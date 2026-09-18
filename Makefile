CXX = g++
CXXFLAGS = -std=c++17 -Wall
SDL_FLAGS = $(shell pkg-config --cflags --libs sdl3)

SRCS = Main.cpp Chip8.cpp Platform.cpp
TARGET = chip8

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(SDL_FLAGS)

clean:
	rm -f $(TARGET)
