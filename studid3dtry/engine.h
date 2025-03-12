#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_ARGVS   64

#include "common.h"
#include "vid.h"
#include "system.h"
#include "zone.h"

typedef struct
{
    // директория игры
    char *basedir;
    // для аллокаторов памяти
    void *membase;
    int memsize;
} engineparms_t;

extern engineparms_t engine_parms;

extern qboolean engine_initialized;
extern double engine_frametime;
extern double realtime;

void Engine_Init(engineparms_t *parms);
void Engine_Shutdown(void);

// engine frame будет вызываться каждый игровой кадр
void Engine_Frame(float time);

#ifdef _WIN32
typedef enum {MS_WINDOWED, MS_FULLSCREEN, MS_FULLDIB, MS_UNINIT} modestate_t;
#endif
