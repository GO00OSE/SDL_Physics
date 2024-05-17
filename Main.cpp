#include <stdio.h>
#include <SDL.h>
#include "Particle.h"
#include "ParticleManager.cpp"
#include "Utils.h"
#include <chrono>

int main(int argc, char* args[]) {
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* renderer;
	SDL_Event Event;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	} 
	else {
		window = SDL_CreateWindow("SDL Physics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			screenSurface = SDL_GetWindowSurface(window);

			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x15, 0x15, 0x15));
			SDL_UpdateWindowSurface(window);

			ParticleManager PM;
			float old_time = std::clock();
			float passedTime;

			bool quit = false;
			while (!quit) {
				while (SDL_PollEvent(&Event)) {
					if (Event.type == SDL_QUIT) {
						quit = true;
					}
					else if (Event.type == SDL_MOUSEBUTTONDOWN) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						//printf("%d, %d\n", x, y);
						
						Particle newParticle = Particle(20, Vec2(x, y), Vec2(0, 0), Vec2(0, 200));
						PM.add(newParticle);
					}
				}
				
				SDL_SetRenderDrawColor(renderer, 0x15, 0x15, 0x15, 0xFF);
				SDL_RenderClear(renderer);
				
				passedTime = float(std::clock()) - old_time;
				old_time = std::clock();

				PM.update(passedTime);
				PM.draw(renderer);
				SDL_RenderPresent(renderer);
			}
		}

		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}
	
	return 0;
}