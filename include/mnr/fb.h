#pragma once

typedef struct{
    unsigned id, tex_id, width, height;
}mr_framebuffer;

mr_framebuffer* mr_create_framebuffer(const unsigned w, const unsigned h);
void mr_bind_framebuffer(mr_framebuffer* fb);
void mr_unbind_framebuffer(void);
void mr_destroy_framebuffer(mr_framebuffer* fb);