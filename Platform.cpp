#include "Platform.hpp"

Platform::Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(title, windowWidth, windowHeight, 0);
	renderer = SDL_CreateRenderer(window, NULL);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
	                              SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
}

Platform::~Platform()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Platform::Update(void const* buffer, int pitch)
{
	SDL_UpdateTexture(texture, nullptr, buffer, pitch);
	SDL_RenderClear(renderer);
	SDL_RenderTexture(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

bool Platform::ProcessInput(uint8_t* keys)
{
	bool quit = false;
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_QUIT:
				quit = true;
				break;

			case SDL_EVENT_KEY_DOWN:
			case SDL_EVENT_KEY_UP:
			{
				bool down = (event.type == SDL_EVENT_KEY_DOWN);
				switch (event.key.key)
				{
					case SDLK_X: keys[0] = down; break;
					case SDLK_1: keys[1] = down; break;
					case SDLK_2: keys[2] = down; break;
					case SDLK_3: keys[3] = down; break;
					case SDLK_Q: keys[4] = down; break;
					case SDLK_W: keys[5] = down; break;
					case SDLK_E: keys[6] = down; break;
					case SDLK_A: keys[7] = down; break;
					case SDLK_S: keys[8] = down; break;
					case SDLK_D: keys[9] = down; break;
					case SDLK_Z: keys[0xA] = down; break;
					case SDLK_C: keys[0xB] = down; break;
					case SDLK_4: keys[0xC] = down; break;
					case SDLK_R: keys[0xD] = down; break;
					case SDLK_F: keys[0xE] = down; break;
					case SDLK_V: keys[0xF] = down; break;
					case SDLK_ESCAPE: quit = true; break;
				}
				break;
			}
		}
	}

	return quit;
}
