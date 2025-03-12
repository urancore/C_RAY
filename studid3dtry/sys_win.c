#include <windows.h>
#include "engine.h"

static double pfreq;
static double curtime = 0.0;
static double lastcurtime = 0.0;
static int lowshift;

qboolean nostdout = false;
HANDLE hinput, houtput;

void Sys_InitFloatTime(void);

void Sys_Init(void)
{
    LARGE_INTEGER PerformanceFreq;
    unsigned int lowpart, highpart;

    if(!QueryPerformanceFrequency(&PerformanceFreq))
        Sys_Error("No hardware timer available");

    lowpart = (unsigned int)PerformanceFreq.LowPart;
    highpart = (unsigned int)PerformanceFreq.HighPart;
    lowshift = 0;

    while (highpart || ((double)lowpart > 2000000.0))
	{
		lowshift++;
		lowpart >>= 1;
		lowpart |= (highpart & 1) << 31;
		highpart >>= 1;
	}

    pfreq = 1.0 / (double)lowpart;

    Sys_InitFloatTime();
}

void Sys_Error(char *error, ...)
{
    va_list argptr;
    char text[1024];

    va_start(argptr, error);
    vsprintf(text, error, argptr);
    va_end(argptr);

    Sys_Printf("Error: %s\n", text);

    MessageBox(NULL, text, "Game Error", MB_OK | MB_ICONERROR);

    Engine_Shutdown();

    exit(1);
}

void Sys_Printf(char *fmt, ...)
{
    va_list argptr;
    char text[1024];
    DWORD dummy;
    int length;

    va_start(argptr, fmt);
    length = vsprintf(text, fmt, argptr);
    va_end(argptr);

    WriteFile(houtput, text, length, &dummy, NULL);
}

void Sys_Quit(void)
{
    Engine_Shutdown();

    if(!nostdout)
        FreeConsole();

    exit(0):
}

double Sys_FloatTime(void)
{
    static int			sametimecount;
	static unsigned int	oldtime;
	static int			first = 1;
	LARGE_INTEGER		PerformanceCount;
	unsigned int		temp, t2;
	double				time;

    QueryPerformanceCounter (&PerformanceCount);

	temp = ((unsigned int)PerformanceCount.LowPart >> lowshift) |
		   ((unsigned int)PerformanceCount.HighPart << (32 - lowshift));

    if (first) {
       oldtime = temp;
       first = 0;
    }
    else {
        if ((temp <= oldtime) && ((oldtime - temp) < 0x10000000))
              oldtime = temp;
        else {
            t2 = temp - oldtime;
       
            time = (double)t2 * pfreq;
            oldtime = temp;
       
            curtime += time;
       
            if (curtime == lastcurtime) {
                sametimecount++;
       
                if (sametimecount > 100000) {
                    curtime += 1.0;
                       sametimecount = 0;
                }
            }
            else
                sametimecount = 0;
       
            lastcurtime = curtime;
        }
    }

    return curtime;
}

void Sys_InitFloatTime(void)
{
    Sys_FloatTime();

    curtime = 0.0;
    lastcurtime = curtime;
}

/* потом для создания окна понадобится */
HINSTANCE global_hInstance;
int global_nCmdShow;

static char *empty_string = "";

BOOL WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    static char cwd[1024];
    engineparms_t parms;
    double time, oldtime, newtime;
    int t;
    char *argv[MAX_NUM_ARGVS];
    int argc;

    /* проверка на слишком старую винду */
    if(hPrevInstance)
        return FALSE;

    global_hInstance = hInstance;
    global_nCmdShow = nCmdShow;

    if(!GetCurrentDirectory(sizeof(cwd), cwd))
        Sys_Error("Couldn't get current directory");

    if(cwd[strlen(cwd)-1] == '/')
        cwd[strlen(cwd)-1] = 0;

    parms.basedir = cwd;

    argc = 0;
    argv[0] = empty_string;

    /* конвертация lpCmdLine в argc и argv*/
    while(*lpCmdLine && (argc < MAX_NUM_ARGVS)) {
		while(*lpCmdLine && ((*lpCmdLine <= 32) || (*lpCmdLine > 126))) {
			lpCmdLine++;
        }
		if(*lpCmdLine) {
			argv[argc] = lpCmdLine;
			argc++;
			while(*lpCmdLine && ((*lpCmdLine > 32) && (*lpCmdLine <= 126))) {
				lpCmdLine++;
            }
			if(*lpCmdLine) {
				*lpCmdLine = 0;
				lpCmdLine++;
			}
		}
	}

    COM_InitArgv(argc, argv);

    nostdout = (COM_CheckParm("-nostdout") != 0);

    parms.memsize = 16 * 1024 * 1024;

    if(COM_CheckParm("-heapsize")) {
        t = COM_CheckParm("-heapsize")+1;
        if(t < com_argc)
            parms.memsize = atoi(com_argv[t]) * 1024;
    }

    parms.membase = malloc(parms.memsize);
    if(!parms.membase) // не удалось выделить память для игры
        Sys_Error("Not enough memory free");

    if(!nostdout) {
        if(!AllocConsole()) {
            Sys_Error("Could not create the console");
        }

        hinput = GetStdHandle(STD_INPUT_HANDLE);
        houtput = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    Sys_Init();

    Sys_Printf("Engine_Init\n");
    Engine_Init(&parms);

    while(1) {
        newtime = Sys_FloatTime();
        time = newtime - oldtime;
        Engine_Frame(time);
        oldtime = newtime;
    }

    return TRUE;
}
