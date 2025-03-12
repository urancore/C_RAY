#include "engine.h"

engineparms_t engine_parms;

qboolean engine_initialized = false;

double engine_frametime; // сколько времени будет длится этот кадр
double realtime = 0.0;
double oldrealtime = 0.0;

/*
 * Если сейчас подходящее время для кадра возвращает true
 * а иначе false
*/

static qboolean Engine_FilterTime(float time)
{
    realtime += time;

    if(realtime - oldrealtime < (1.0/60.0))
        return false;

    engine_frametime = realtime - oldrealtime;
    oldrealtime = realtime;

    if(engine_frametime > 0.1)
        engine_frametime = 0.1;
    if(engine_frametime < 0.001)
        engine_frametime = 0.001;

    return true;
}

void Engine_Frame(float time)
{
    if(!Engine_FilterTime(time)) // ограничение fps
        return;

    void *buf = Hunk_Alloc(64);
    Sys_Printf("Allocated 64 bytes at 0x%p\n", buf);

    // обновлять всё что можно
}

void Engine_Init(engineparms_t *parms)
{
    Memory_Init(parms->membase, parms->memsize);

    Sys_Printf("Version: "__TIME__" "__DATE__"\n");

    VID_Init();

    engine_initialized = true;

    Sys_Printf("===================== Game Initialized ======================\n");
}

void Engine_Shutdown(void)
{

}
