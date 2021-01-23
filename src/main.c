#include <glad/glad.h>
#include "mnr/window.h"
#include "mnr/file.h"
#include "mnr/texture.h"
#include "mnr/input.h"
#include "mnr/vmath.h"

void keypress_handler(uint32_t key)
{
}

int main(int argc, char** argv)
{
	const unsigned width = 1280, height = 720;
	puts("Monroe Framework 1.4 devx1");

	mr_init_fs(argv[0]);
	mr_init_window("Monroe", width, height);

	mr_keypressed_ptr = keypress_handler;

	mr_texture *mnro = mr_create_texture("adv/cone_cap_look.png");

	fixed x = 0, y = 0;
	
	int quitter = 0;
	SDL_Event e;
	while(!quitter){
		while(SDL_PollEvent(&e)){
			mr_handler_input(&e);
			if(e.type == SDL_QUIT)
				quitter = 1;
		}

		if(keys_arr[SDL_SCANCODE_ESCAPE])
			quitter = 1;

		mr_handler_mouse();

		SDL_RenderClear(mwin->rdr);

		SDL_RenderPresent(mwin->rdr);
	}
	
	mr_destroy_texture(mnro);
	
	mr_destroy_window();
	mr_destroy_fs();
    return 0;
}
