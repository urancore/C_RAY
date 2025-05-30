/*
 * Закрывает игру и говорит об ошибке
*/
void Sys_Error(char *fmt, ...);

/*
 * Печатает текст в консоль ОС
*/
void Sys_Printf(char *fmt, ...);

/*
 * Получить текущее время в секундах с точностью до микросекунд
*/
double Sys_FloatTime(void);

void sys_message_box(char message_type, const char* title, const char* text);
void window_initialize(const char* window_title);
int window_process_messages(void);
void window_show(void);
void window_destroy(void);
