#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600

struct Circle {
	double x;
	double y;
	double radius;
};

void FillCircle(SDL_Surface *surface, struct Circle circle, Uint32 color) {
	double radius_sq = circle.radius * circle.radius;

	for (double x = circle.x - circle.radius; x <= circle.x + circle.radius; x++) {
		for (double y = circle.y - circle.radius; y <= circle.y + circle.radius; y++) {
			double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
			if (distance_squared < radius_sq) {
				SDL_Rect pixel = (SDL_Rect){x, y, 1, 1};
				SDL_FillRect(surface, &pixel, color);
			}
		};
	};
}

int main(int argc, char **args) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Init Error %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window *window =
	    SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface *screen_surface = SDL_GetWindowSurface(window);
	SDL_Delay(2000);

	struct Circle circle = {200, 200, 100};

	bool isWindowOpen = true;
	SDL_Event event;

	while (isWindowOpen) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isWindowOpen = false;
			}
			if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
				isWindowOpen = false;
			}
		}
		FillCircle(screen_surface, circle, 0xAA15EE);
		SDL_UpdateWindowSurface(window);
		SDL_Delay(20);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}