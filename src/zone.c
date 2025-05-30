#include "ray.h"

#define ZONEID 0x1d4a11

typedef struct
{
    int size;
    memblock_t blocklist; // начало/конец связанного списка
    memblock_t *rover;
} memzone_t;

memzone_t *mainzone;

// минимальный размер блока, чтобы блоки не разбивались на слишком маленькие
#define MINFRAGMENT 64

void *Z_Malloc(int size)
{
	(void)size;
    // memblock_t *base, *rover, *start;

    // size = (size + 3) & ~3; // выравнивание размера по 4 байтам (хз зачем)
    // size += sizeof(memblock_t);

    // base = mainzone->rover;

    // // если перед "rover" блоком есть свободный блок начать перебирать с него
    // if(!base->prev->used)
 	// 	base = base->prev;

    // rover = base;
    // start = base->prev; // пофиксил

    // перебор всех блоков, пока не найдётся свободный и с подходящим размером
    // do {
    //     if(rover == start) {
    //         // перебрали все блоки и не нашли нужного
    //         Sys_Error("Z_Malloc: failed on allocation of %i bytes", size);
    //     }

    //     if(rover->used) {
    //         base = base->prev;
    //         //Z_Free((byte*)rover+sizeof(memblock_t));
    //         base = base->next;
    //         rover = base->next;
    //     } else {
    //         rover = rover->next;
    //     }
    // } while(base->used || base->size < size);

    return NULL;
}

void Memory_Init(void *buf, int size)
{
    memblock_t *block;

    mainzone = (memzone_t*)buf;
    mainzone->size = size;

    // сначала выделить под один блок всю память, потом он будет разбиваться на другие
    mainzone->blocklist.next = mainzone->blocklist.prev =
        block = (memblock_t*)((byte*)mainzone + sizeof(memzone_t));

    mainzone->blocklist.used = 1;
    mainzone->rover = block;

    block->prev = block->next = &mainzone->blocklist;
    block->used = 0; // единственный блок будет свободным для того чтобы его можно было разбить на другие

    block->size = mainzone->size - sizeof(memzone_t);
}
