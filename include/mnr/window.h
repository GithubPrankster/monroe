#pragma once
#include <SDL2/SDL.h>

/*
	This structure is a convinient wrapper
	around SDL2/GL. Treat it as such.
*/

typedef struct{
    SDL_Window* win;
    SDL_GLContext ctx;
    uint32_t w, h;
}mr_window;

extern mr_window* mwin;

int mr_init_window(const char* name, uint32_t uw, uint32_t uh);
void mr_destroy_window(void);
