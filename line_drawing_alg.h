#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include "structs.h"

void bresennhams_alg(int x0, int y0, int x1, int y1, SDL_Surface *surface, Uint32 color, int HEIGHT, int WIDTH);