#pragma once

typedef struct{
	unsigned id, w, h;
}mr_texture;

mr_texture *mr_create_texture(const char* path);
void mr_bind_texture(const unsigned tex, const unsigned slot);
void mr_destroy_texture(mr_texture* tex);
