#include "mnr/texture.h"
#include "mnr/file.h"
#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

#include <stdlib.h>
#include <stdio.h>

mr_texture *mr_create_texture(const char* path)
{
	size_t len = 0;
	unsigned char* odata = (unsigned char*)mr_load_file(path, &len);
	int w, h;
	unsigned char *data = stbi_load_from_memory(odata, len, &w, &h, NULL, 4);
	free(odata);
	if(!data){
		printf("[MONROE]: Could not load texture %s.\n", path);
		return NULL;
	}

	mr_texture *tex = malloc(sizeof tex);
	if(!tex){
		printf("[MONROE]: Could not allocate for texture %s.\n", path);
		stbi_image_free(data);	
		return NULL;
	}

	tex->w = w;
	tex->h = h;

	tex->data = data;
	
	return tex;
}

void mr_render_texture(mr_texture* tex)
{

}

void mr_destroy_texture(mr_texture* tex)
{
	if(tex){
		stbi_image_free(tex->data);
		free(tex);
	}
}

