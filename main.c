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

#include "line_drawing_alg.h"

#define RAYS_NUMBER 100

#define WIDTH 1500
#define HEIGHT 600
#define LENGTH (int)(sqrt((WIDTH) * (WIDTH) + (HEIGHT) * (HEIGHT)))

struct Circle {
	int x;
	int y;
	double radius;
};

struct Ray {
	int start_x;
	int start_y;
	double angle;
	int end_x;
	int end_y;
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

void find_angles(struct Circle circle, struct Ray rays[RAYS_NUMBER]) {
	for (int i = 0; i < RAYS_NUMBER; ++i) {
		double deg = 360.0 * i / RAYS_NUMBER;
		double theta = deg * M_PI / 180.0;

		rays[i].angle = theta;
	}
}

void find_rays(struct Circle circle, struct Ray rays[RAYS_NUMBER]) {
	for (int i = 0; i < RAYS_NUMBER; ++i) {
		rays[i].start_x = circle.x;
		rays[i].start_y = circle.y;
		rays[i].end_x = circle.x + LENGTH * sin(rays[i].angle);
		rays[i].end_y = circle.y + LENGTH * cos(rays[i].angle);
	}
}

void draw_rays(struct Ray rays[RAYS_NUMBER], SDL_Surface *surface, Uint32 color) {
	for (int i = 0; i < RAYS_NUMBER; ++i) {
		bresennhams_alg(rays[i].start_x, rays[i].start_y, rays[i].end_x, rays[i].end_y, surface, color, HEIGHT, WIDTH);
	}
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

	struct Circle circle = {-200, -200, 30};
	struct Circle circle_shadow = {(WIDTH / 5) * 4, (HEIGHT / 5) * 2, 120};
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
}