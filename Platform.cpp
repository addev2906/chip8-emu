#include "headers/Platform.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_audio.h>
#include <cstdint>

Platform::Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow(title, windowWidth, windowHeight, 0);
	renderer = SDL_CreateRenderer(window, NULL);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	SDL_AudioSpec spec;
    spec.freq = 44100;
    spec.channels = 1;
    spec.format = SDL_AUDIO_F32;

    audioStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);

    // Start the stream once and leave it running indefinitely
    SDL_ResumeAudioStreamDevice(audioStream);
}

Platform::~Platform()
{
    if (audioStream) {
        SDL_DestroyAudioStream(audioStream);
    }
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
void Platform::ProcessAudio(uint8_t soundTimer) {
    while (SDL_GetAudioStreamAvailable(audioStream) < 8192) {
            float sampleBuffer[512];
            const float amplitude = 0.1f;
            const int halfPeriod = 44100 / 440 / 2; // 50 samples per half-wave at 440Hz

            for (int i = 0; i < 512; ++i) {
                if (soundTimer > 0) {
                    // Generate square wave
                    sampleBuffer[i] = ((audioPhase / halfPeriod) % 2 == 0) ? amplitude : -amplitude;
                } else {
                    // Generate silence
                    sampleBuffer[i] = 0.0f;
                }

                // Advance phase and wrap cleanly at 44100 to prevent integer overflow
                audioPhase = (audioPhase + 1) % 44100;
            }

            SDL_PutAudioStreamData(audioStream, sampleBuffer, sizeof(sampleBuffer));
        }
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
