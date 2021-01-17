#include "mnr/audio.h"
#include "mnr/file.h"

#undef STB_VORBIS_HEADER_ONLY
#include "external/stb_vorbis.c"

#define CUTE_SOUND_FORCE_SDL
#define CUTE_SOUND_IMPLEMENTATION
#include "external/cute_sound.h"

#define DEFAULT_RATE 44100
#define SOUND_BUFFER 2048
#define SLEEP_MS 5

static cs_context_t* ctx = NULL;

void mr_init_sound(void)
{
	ctx = cs_make_context(NULL, DEFAULT_RATE, SOUND_BUFFER, 0, NULL);
	if(!ctx){
		printf("[CUTE_SOUND]: %s\n", cs_error_reason);
		return;
	}
	cs_spawn_mix_thread(ctx);
	cs_thread_sleep_delay(ctx, SLEEP_MS);
}

cs_loaded_sound_t mr_load_wav(const char* path)
{
	cs_loaded_sound_t sound = { 0, 0, 0, 0, { NULL, NULL } };
	size_t size;
	char* wav = (char*)mr_load_file(path, &size);
	cs_read_mem_wav(wav, size, &sound);
	CUTE_SOUND_FREE(wav, NULL);
	return sound;
}

cs_loaded_sound_t mr_load_ogg(const char* path)
{
	size_t length = 0;
	unsigned char* memory = (unsigned char*)mr_load_file(path, &length);
	cs_loaded_sound_t sound = { 0, 0, 0, 0, { NULL, NULL } };
	cs_read_mem_ogg(memory, length, &sound);
	CUTE_SOUND_FREE(memory, NULL);
	return sound;
}

void mr_play_sound(cs_playing_sound_t* snd)
{
	if(!cs_insert_sound(ctx, snd))
		printf("[CUTE_SOUND]: %s\n", cs_error_reason);
}

void mr_destroy_sound(void)
{
	if(ctx)
		cs_shutdown_context(ctx);
}
