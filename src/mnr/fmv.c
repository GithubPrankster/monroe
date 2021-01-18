#include "mnr/fmv.h"

#include "mnr/file.h"

#define PL_MPEG_IMPLEMENTATION
#include "external/pl_mpeg.h"

static plm_t* ctx = NULL;

void mr_create_fmv(const char* fmv)
{
    size_t sz = 0;
    uint8_t* data = (uint8_t*)mr_load_file(fmv, &sz);
    if(!sz){
        printf("[MONROE]: Could not load FMV %s.\n", fmv);
        return;
    }

    ctx = plm_create_with_memory(data, sz, 0);
    free(data);
    if(!ctx){
        printf("[MONROE]: Could not initialize FMV %s.\n", fmv);
    }
}

void mr_destroy_fmv(const char* fmv)
{
    plm_destroy(ctx);
}