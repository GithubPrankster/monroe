#include "mnr/window.h"
#include <glad/glad.h>

#define SDL2_RERROR() printf("[SDL2]: %s\n", SDL_GetError())
#define WPC SDL_WINDOWPOS_CENTERED

mr_window* mwin;

int mr_init_window(const char* name, uint32_t uw, uint32_t uh)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		SDL2_RERROR();
		return -1;
	}

	mwin = malloc(sizeof mwin);
	if(!mwin){
		puts("[MONROE]: Could not allocate main window.");
		SDL_Quit();
		return -1;
	}

	mwin->w = uw;
	mwin->h = uh;

	mwin->win = SDL_CreateWindow(name, WPC, WPC, uw, uh, SDL_WINDOW_SHOWN);
	if(!mwin->win){
		SDL2_RERROR();
		free(mwin);
		SDL_Quit();
		return -1;
	}

	mwin->rdr = SDL_CreateRenderer(mwin->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!mwin->rdr){
		SDL2_RERROR();
		SDL_DestroyWindow(mwin->win);
		free(mwin);
		SDL_Quit();
		return -1;
	}

	return 0;
}

void mr_destroy_window(void)
{
	if(mwin){
		if(mwin->rdr)
			SDL_DestroyRenderer(mwin->rdr);
		if(mwin->win)
			SDL_DestroyWindow(mwin->win);
		free(mwin);
	}
}
