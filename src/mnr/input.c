#include "mnr/input.h"

int mouse_x = 0, mouse_y = 0;
uint8_t keys_arr[SDL_NUM_SCANCODES];
uint8_t mouse_buttons[16];
void (*mr_keypressed_ptr)(uint32_t) = NULL;

void mr_handler_input(SDL_Event *e)
{
    switch(e->type){
        case SDL_KEYDOWN:
            keys_arr[e->key.keysym.scancode] = 1;
            if (e->key.repeat == 0 && mr_keypressed_ptr)
                mr_keypressed_ptr(e->key.keysym.scancode);
            break;
        case SDL_KEYUP:
            keys_arr[e->key.keysym.scancode] = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouse_buttons[e->button.button] = 1;
            break;
        case SDL_MOUSEBUTTONUP:
            mouse_buttons[e->button.button] = 1;
            break;
    }
}

void mr_handler_mouse(void)
{
    if(SDL_GetRelativeMouseMode())
        SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
    else
        SDL_GetMouseState(&mouse_x, &mouse_y);
}