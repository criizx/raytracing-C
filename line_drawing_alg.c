#include "line_drawing_alg.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bresennhams_alg(int x0, int y0, int x1, int y1, SDL_Surface *surface, Uint32 color, int HEIGHT, int WIDTH) {
	int steep = 0;
	if (x0 < 0 || x0 >= WIDTH || y0 < 0 || y0 >= HEIGHT) {
		return;
	}

	if (abs(x0 - x1) < abs(y0 - y1)) {
		swap(&x0, &y0);
		swap(&x1, &y1);
		steep = 1;
	}
	if (x0 > x1) {
		swap(&x0, &x1);
		swap(&y0, &y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			SDL_Rect rect = {y, x, 1, 1};
			SDL_FillRect(surface, &rect, color);

		} else {
			SDL_Rect rect = {x, y, 1, 1};
			SDL_FillRect(surface, &rect, color);
		}
		error2 += derror2;
		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}