#include "ray.h"

void load_map(void)
{
	FILE *file = fopen("map.map", "rb");
	if (file) {
		fread(map, sizeof(unsigned char), MAP_WIDTH * MAP_HEIGHT, file);
		fclose(file);
	}
}

void save_map(void)
{
	FILE *file = fopen("map.map", "wb");
	if (file) {
		fwrite(map, sizeof(unsigned char), MAP_WIDTH * MAP_HEIGHT, file);
		fclose(file);
	}
}
