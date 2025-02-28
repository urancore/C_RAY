#include "ray.h"

void sys_error(char *fmt, ...)
{
    char text[1024];
    va_list argptr;

    va_start(argptr, fmt);
    vsprintf(text, fmt, argptr);
    va_end(argptr);

    MessageBox(NULL, text, "Game Error", MB_OK | MB_ICONERROR);

    // TODO: сохранить все что не сохранено

    exit(1);
}

void sys_printf(char *fmt, ...)
{
    char text[1024];
    va_list argptr;

    va_start(argptr, fmt);
    vsprintf(text, fmt, argptr);
    va_end(argptr);

    // TODO: сделать лог в файл
    printf(text);
}

void sys_message_box(char message_type, const char *text)
{
	UINT type = MB_OK;
	const char *title = "Information"; // default
	switch (message_type)
	{
	case 'i': // info
		type |= MB_ICONINFORMATION;
		break;
	case 'e': // error
		type |= MB_ICONERROR;
		title = "Error";
		break;
	case 'w': // warning
		type |= MB_ICONWARNING;
		title = "Warning";
		break;
	case 'q': // question
		type |= MB_YESNO | MB_ICONQUESTION;
		title = "Question";
		break;
	default:
		break;
	}
	MessageBox(NULL, text, title, type);
}
