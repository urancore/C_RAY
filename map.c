#include <stdio.h>

#include "c_ray.h"

void load_map(unsigned char map_data[MAP_HEIGHT][MAP_WIDTH])
{
    FILE *file = fopen("map.map", "rb");
    if (file) {
        fread(map_data, sizeof(unsigned char), MAP_WIDTH * MAP_HEIGHT, file);
        fclose(file);
    }
}