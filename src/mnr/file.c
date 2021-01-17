#include "mnr/file.h"
#include <physfs.h>
#include <stdio.h>
#include <stdlib.h>

#define PHYSFS_ERR PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())

void mr_init_fs(const char* argv)
{
	PHYSFS_init(argv);
	PHYSFS_mount(PHYSFS_getBaseDir(), NULL, 1);
	PHYSFS_mount("archive.7z", NULL, 1);
}

char* mr_load_file(const char* path, size_t* sz)
{
	if(!PHYSFS_exists(path)){
		printf("[PHYSFS]: %s %s\n", path, PHYSFS_ERR);
		return NULL;
	}

	PHYSFS_file *fp;
	fp = PHYSFS_openRead(path);

	size_t size = PHYSFS_fileLength(fp);
	if(sz)
		*sz = size;

	char* buf = malloc(size + 1);
	if(!buf){
		printf("[MONROE]: Unable to allocate file %s.\n", path);
		PHYSFS_close(fp);
		if(sz)
			*sz = 0;
		return NULL;
	}

	PHYSFS_readBytes(fp, buf, size);
	buf[size] = '\0';

	PHYSFS_close(fp);
	return buf;
}

void mr_set_fs(const char* path)
{
	if(!PHYSFS_mount(path, NULL, 1))
		printf("[PHYSFS]: %s\n", PHYSFS_ERR);
}

void mr_destroy_fs(void)
{
	PHYSFS_deinit();
}
