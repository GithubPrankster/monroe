#include "mnr/fb.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

mr_framebuffer* mr_create_framebuffer(const unsigned w, const unsigned h)
{
    mr_framebuffer* fb = malloc(sizeof fb);
	if(!fb){
		puts("[MONROE]: Could not allocate framebuffer.");
		return NULL;
	}
    fb->width = w;
    fb->height = h;

    glGenFramebuffers(1, &fb->id);
    glBindFramebuffer(GL_FRAMEBUFFER, fb->id);

    glGenTextures(1, &fb->tex_id);
    glBindTexture(GL_TEXTURE_2D, fb->tex_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb->tex_id, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        puts("[MONROE]: Framebuffer incomplete.");

        glDeleteTextures(1, &fb->tex_id);
        glDeleteFramebuffers(1, &fb->id);
        free(fb);

        return NULL;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return fb;
}

void mr_bind_framebuffer(mr_framebuffer* fb)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fb->id);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, fb->width, fb->height); /* Thanks to Dan Bechard (dandymcgee) for helping out! */
}

void mr_unbind_framebuffer(const unsigned og_w, const unsigned og_h)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, og_w, og_h);
}

void mr_destroy_framebuffer(mr_framebuffer* fb)
{
    if(fb){
        glDeleteTextures(1, &fb->tex_id);
        glDeleteFramebuffers(1, &fb->id);
        free(fb);
    }
}