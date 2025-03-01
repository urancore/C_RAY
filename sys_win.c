/*
 * реализация системных функций и точки входа специально для винды
*/

#include "ray.h"

// static double pfreq;
// static double curtime = 0.0;
// static double lastcurtime = 0.0;
// static int lowshift;
// qboolean console = false;
// HANDLE hinput, houtput;

// void Sys_InitFloatTime(void);

void Sys_Error(char* fmt, ...)
{
    char text[1024];
    va_list argptr;

    va_start(argptr, fmt);
    vsprintf(text, fmt, argptr);
    va_end(argptr);

    Sys_Printf("Error: %s\n", text);

    MessageBox(NULL, text, "Game Error", MB_OK | MB_ICONERROR);

    // Game_Shutdown(), или типа того

    exit(1);
}

void Sys_Printf(char *fmt, ...) {
	char text[1024];
	va_list argptr;

	va_start(argptr, fmt);
	vsprintf(text, fmt, argptr);
	va_end(argptr);

    fprintf(stderr, text, argptr);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

void sys_message_box(char message_type, const char* title, const char* text)
{
	UINT type = MB_OK;
	switch (message_type)
	{
	case 'i': // info
		type |= MB_ICONINFORMATION;
		break;
	case 'e': // error
		type |= MB_ICONERROR;
		break;
	case 'w': // warning
		type |= MB_ICONWARNING;
		break;
	case 'q': // question
		type |= MB_YESNO | MB_ICONQUESTION;
		break;
	default:
		break;
	}
	MessageBox(NULL, text, title, type);
}

void window_destroy(void)
{
	DestroyWindow(window);
}

void window_initialize(const char* window_title)
{
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WndProc; // ещё раз скомпиль должно сработать
    wc.lpszClassName = "CRayWindow";
    RegisterClassA(&wc);

    window = CreateWindowExA(0, "CRayWindow", window_title,
        WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
        0, 0, WW, WH, NULL, NULL, NULL, NULL);
}

void window_show(void)
{
	ShowWindow(window, SW_SHOWNORMAL);
}

int window_process_messages(void)
{
    MSG msg;
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if(msg.message == WM_QUIT)
            return 0;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 1;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg) {
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_DESTROY:
			return 0;
		default:
			return DefWindowProcA(hwnd, msg, wparam, lparam);
	}
	return 0;
}
