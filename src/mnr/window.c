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

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mwin = malloc(sizeof mwin);
	if(!mwin){
		puts("[MONROE]: Could not allocate main window.");
		SDL_Quit();
		return -1;
	}

	mwin->w = uw;
	mwin->h = uh;

	mwin->win = SDL_CreateWindow(name, WPC, WPC, uw, uh, SDL_WINDOW_OPENGL);
	if(!mwin->win){
		SDL2_RERROR();
		free(mwin);
		SDL_Quit();
		return -1;
	}

	mwin->ctx = SDL_GL_CreateContext(mwin->win);
	if(!mwin->ctx){
		SDL2_RERROR();
		SDL_DestroyWindow(mwin->win);
		free(mwin);
		SDL_Quit();
		return -1;
	}

	if(!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)){
		SDL_GL_DeleteContext(mwin->ctx);
		SDL_DestroyWindow(mwin->win);
		free(mwin);
		SDL_Quit();
		return -1;
	}

	SDL_GL_SetSwapInterval(1);

	glViewport(0, 0, uw, uh);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return 0;
}

void mr_destroy_window(void)
{
	if(mwin){
		if(mwin->ctx)
			SDL_GL_DeleteContext(mwin->ctx);
		if(mwin->win)
			SDL_DestroyWindow(mwin->win);
		free(mwin);
	}
}
