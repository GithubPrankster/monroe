#pragma once

/*
	Convinient wrapper around loading files using
	PhysFS. Be ready to call `free()` once 
	you're done with the file..
*/

#include <stddef.h>

void mr_init_fs(const char* argv);
char* mr_load_file(const char* path, size_t* sz);
void mr_set_fs(const char* path);
void mr_destroy_fs(void);
