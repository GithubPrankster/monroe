#pragma once

#define STB_VORBIS_HEADER_ONLY
#include "external/stb_vorbis.c"

#include "external/cute_sound.h"

#define SET_PLAY_VOL(snd, vol) cs_set_volume(&snd, vol, vol)
/* This macro allows you to utilize -1 to 1 ranges for panning instead of 0 to 1.*/
#define SET_PLAY_PAN(snd, pin) cs_set_pan(&snd, (pin + 1.0f) / 2.0f)

void mr_init_sound(void);
void mr_play_sound(cs_playing_sound_t* snd);
void mr_destroy_sound(void);