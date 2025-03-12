typedef unsigned char byte;

#undef true
#undef false
typedef enum {false,true} qboolean;

extern int com_argc;
extern char **com_argv;

/*
 * Проверить, есть ли аргумент в аргументах коммандной строки
 * если есть возвращает его индекс в com_argv
 * если нет, то 0
*/
int COM_CheckParm(char *parm);

/*
 * Инициализировать парсер аргументов
*/
void COM_InitArgv(int argc, char **argv);
