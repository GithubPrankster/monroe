#include "mnr/texture.h"
#include "mnr/file.h"
#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

#include <glad/glad.h>

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

	glGenTextures(1, &tex->id);
	tex->w = w;
	tex->h = h;

	glBindTexture(GL_TEXTURE_2D, tex->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);
	return tex;
}

void mr_destroy_texture(mr_texture* tex)
{
	if(tex){
		glDeleteTextures(1, &tex->id);
		free(tex);
	}
}

