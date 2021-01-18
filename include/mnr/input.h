#pragma once

/*
    Monroe Framework Input
    Based off exezin's exengine implementations
*/

#include <SDL2/SDL.h>

extern int mouse_x, mouse_y;
// This array holds either held down or disabled.
extern uint8_t keys_arr[SDL_NUM_SCANCODES];
extern uint8_t mouse_buttons[16];
extern void (*mr_keypressed_ptr)(uint32_t);

void mr_handler_input(SDL_Event *e);
void mr_handler_mouse(void);