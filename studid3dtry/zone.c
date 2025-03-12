#include "engine.h"

void Z_Free(void *ptr)
{
    (void)ptr;
}

void *Z_Malloc(int size)
{
    (void)size;
    return NULL;
}

void *Z_TagMalloc(int size, int tag)
{
    (void)size;
    (void)tag;
    return NULL;
}

#define	HUNK_SENTINAL	0x1df001ed

typedef struct
{
    int sentinal;
    int size;
    char name[8];
} hunk_t;

byte *hunk_base;
int hunk_size;
int hunk_low_used;

void *Hunk_AllocName(int size, char *name)
{
    hunk_t *h;

    if(size < 0)
        Sys_Error("Hunk_Alloc: bad size %i", size);

    size = sizeof(hunk_t) + ((size+15) & ~15);

    if(hunk_size - hunk_low_used < size)
        Sys_Error("Hunk_Alloc: failed on %i bytes", size);

    h = (hunk_t*)(hunk_base + hunk_low_used);
    hunk_low_used += size;

    memset(h, 0, size);

    h->size = size;
    h->sentinal = HUNK_SENTINAL;
    strncpy(h->name, name, 8);

    return (void*)(h+1);
}

void *Hunk_Alloc(int size)
{
    return Hunk_AllocName(size, "unknown");
}

int Hunk_LowMark(void)
{
    return hunk_low_used;
}

void Hunk_FreeToLowMark(int mark)
{
    if(mark < 0 || mark > hunk_low_used)
        Sys_Error("Hunk_FreeToLowMark: bad mark %i", mark);

    memset(hunk_base + mark, 0, hunk_low_used - mark);
    hunk_low_used = mark;
}

void Memory_Init(void *buf, int size)
{
    hunk_base = buf;
    hunk_size = size;
    hunk_low_used = 0;
}
