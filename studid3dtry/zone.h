void Memory_Init(void *buf, int size);

void Z_Free(void *ptr);
void *Z_Malloc(int size);
void *Z_TagMalloc(int size, int tag);

void *Hunk_Alloc(int size);
void *Hunk_AllocName(int size, char *name);
int Hunk_LowMark(void);
void Hunk_FreeToLowMark(int mark);
