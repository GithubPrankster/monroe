#pragma once

typedef struct{
	unsigned id, w, h;
}mr_texture;

mr_texture *mr_create_texture(const char* path);
void mr_destroy_texture(mr_texture* tex);
