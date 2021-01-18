#include <glad/glad.h>
#include "mnr/window.h"
#include "mnr/file.h"
#include "mnr/shader.h"
#include "mnr/quad.h"
#include "mnr/texture.h"
#include "mnr/audio.h"
#include "mnr/fb.h"
#include "mnr/input.h"

static int pausey = 1;

void keypress_handler(uint32_t key)
{
	if(key == SDL_SCANCODE_E)
		pausey ^= 1;
}

int main(int argc, char** argv)
{
	const unsigned width = 1280, height = 720;
	puts("Monroe Framework 1.2 dev3");

	mr_init_fs(argv[0]);
	mr_init_window("Monroe", width, height);
	mr_init_sound();

	mr_keypressed_ptr = keypress_handler;

	cs_loaded_sound_t eurobeat = mr_load_ogg("audio/step-inside.ogg");
	cs_playing_sound_t jump =  cs_make_playing_sound(&eurobeat);
	SET_PLAY_VOL(jump, 0.25f);
	mr_play_sound(&jump);

	unsigned prg = mr_create_shader("shaders/basic.vs", "shaders/basic.fs");
	glUseProgram(prg);
	mr_shader_int(prg, "tex", 0);

	unsigned fbprg = mr_create_shader("shaders/fb.vs", "shaders/fb.fs");
	glUseProgram(fbprg);
	mr_shader_int(fbprg, "tex", 0);

	mr_texture *mnro = mr_create_texture("adv/monroe.png");

	mr_quad *qd = mr_create_quad();

	mr_framebuffer *fb = mr_create_framebuffer(320, 180);

	mat4 model = mat4i;
	mat4_scale(model, v3((float)mnro->w, (float)mnro->h, 0.0f));
	mat4_translate(model, v3((float)mnro->w, (float)mnro->h, 0.0f));

	mat4 proj = mat4i;
	mat4_ortho(proj, 0.0f, 640.f, 360.f, 0.0f, 0.0f, 1.0f);
	
	glClearColor(0.1, 0.1, 0.6, 1.0);
	int quitter = 0;
	SDL_Event e;
	while(!quitter){
		while(SDL_PollEvent(&e)){
			mr_handler_input(&e);
			if(e.type == SDL_QUIT)
				quitter = 1;
		}

		mr_handler_mouse();

		if(keys_arr[SDL_SCANCODE_ESCAPE])
			quitter = 1;

		cs_pause_sound(&jump, pausey);

		/* PSX-Like Step */
		mr_bind_framebuffer(fb);

		mr_bind_texture(mnro->id, 0);

		glUseProgram(prg);
		mr_shader_mat4(prg, "model", model);
		mr_shader_mat4(prg, "proj", proj);

		mr_render_quad(qd);

		/* Finished Step */
		mr_unbind_framebuffer(width, height);

		mr_bind_texture(fb->tex_id, 0);

		glUseProgram(fbprg);

		mr_render_quad(qd);

		SDL_GL_SwapWindow(mwin->win);
	}
	
	mr_destroy_texture(mnro);
	mr_destroy_quad(qd);

	glDeleteProgram(fbprg);
	glDeleteProgram(prg);

	cs_free_sound(&eurobeat);
	
	mr_destroy_sound();
	mr_destroy_window();
	mr_destroy_fs();
    return 0;
}
