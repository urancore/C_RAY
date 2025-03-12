#include "engine.h"

static char *largv[MAX_NUM_ARGVS + 1];
static char *argvdummy = " ";

int com_argc;
char **com_argv;

int COM_CheckParm(char *parm)
{
    int i;

    for(i = 1; i < com_argc; i++) {
        if(com_argv[i] == NULL) // пропускать пустые аргументы
            continue;
        if(strcmp(parm, com_argv[i]) == 0)
            return i;
    }

    return 0;
}

void COM_InitArgv(int argc, char **argv)
{
    for(com_argc = 0; (com_argc<MAX_NUM_ARGVS) && (com_argc < argc); com_argc++) {
        largv[com_argc] = argv[com_argc];
    }

    largv[com_argc] = argvdummy;
    com_argv = largv;
}
