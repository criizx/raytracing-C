#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "limits_to_ray.h"

#define RAYS_NUMBER 100
#define WIDTH 1500
#define HEIGHT 600

void FillCircle(SDL_Surface *surface, struct Circle circle, Uint32 color) {
	double radius_sq = circle.radius * circle.radius;
	for (int x = (int)(circle.x - circle.radius); x <= (int)(circle.x + circle.radius); x++) {
		for (int y = (int)(circle.y - circle.radius); y <= (int)(circle.y + circle.radius); y++) {
			double dx = x - circle.x;
			double dy = y - circle.y;
			if (dx * dx + dy * dy < radius_sq) {
				SDL_Rect pixel = {x, y, 1, 1};
				SDL_FillRect(surface, &pixel, color);
			}
		}
	}
}

void find_angles(struct Circle circle, struct Ray rays[RAYS_NUMBER]) {
	for (int i = 0; i < RAYS_NUMBER; ++i) {
		double deg = 360.0 * i / RAYS_NUMBER;
		rays[i].angle = deg * M_PI / 180.0;
	}
}

void find_rays(struct Circle circle, struct Ray rays[RAYS_NUMBER]) {
	for (int i = 0; i < RAYS_NUMBER; ++i) {
		compute_ray_endpoint(&rays[i], circle, WIDTH, HEIGHT);
	}
}

void draw_rays(struct Ray rays[RAYS_NUMBER], SDL_Surface *surface, Uint32 color) {
	for (int i = 0; i < RAYS_NUMBER; ++i) {
		bresennhams_alg(rays[i].start_x, rays[i].start_y, rays[i].end_x, rays[i].end_y, surface, color, HEIGHT, WIDTH);
	}
}

int main(int argc, char **argv) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Init Error %s\n", SDL_GetError());
		return 1;
	}
	SDL_Window *window =
	    SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface *screen_surface = SDL_GetWindowSurface(window);

	struct Circle circle = {-200, -200, 30};
	struct Circle circle_shadow = {(WIDTH * 4) / 5, (HEIGHT * 2) / 5, 120};
	SDL_Rect erase_rect = {0, 0, WIDTH, HEIGHT};

	bool isWindowOpen = true;
	SDL_Event event;
	struct Ray rays[RAYS_NUMBER];

	find_angles(circle, rays);
	find_rays(circle, rays);

	while (isWindowOpen) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isWindowOpen = false;
			}
			if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
				circle.x = event.motion.x;
				circle.y = event.motion.y;
				find_rays(circle, rays);
			}
		}

		SDL_FillRect(screen_surface, &erase_rect, 0x000000);
		FillCircle(screen_surface, circle, 0xFFFFFF);
		draw_rays(rays, screen_surface, 0xFFFFFF);

		FillCircle(screen_surface, circle_shadow, 0xFFFFFF);

		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
