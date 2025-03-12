/*
 * Сообщить об ошибке и закрыть игру
*/
void Sys_Error(char *error, ...);

/*
 * Написать текст в консоль
*/
void Sys_Printf(char *fmt, ...);

/*
 * Закрыть игру
*/
void Sys_Quit(void);

/*
 * Получить текущее время в секундах
*/
double Sys_FloatTime(void);
