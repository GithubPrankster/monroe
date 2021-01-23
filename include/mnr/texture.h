#pragma once

#include <SDL2/SDL.h>

typedef struct{
	uint8_t* data;
	unsigned w, h;
}mr_texture;

mr_texture *mr_create_texture(const char* path);
void mr_render_texture(mr_texture* tex);
void mr_destroy_texture(mr_texture* tex);
