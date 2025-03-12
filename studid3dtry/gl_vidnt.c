#include "engine.h"
#include <windows.h>


#define MAX_MODE_LIST   30

#define MODE_WINDOWED			0
#define NO_MODE					(MODE_WINDOWED - 1)
#define MODE_FULLSCREEN_DEFAULT	(MODE_WINDOWED + 1)

typedef struct
{
    modestate_t type;
    int width;
    int height;
    int modenum;
    int dib;
    int fullscreen;
    int bpp;
    int halfscreen;
    chgar modedesc[17];
} vmode_t;

static vmode_t modelist[MAX_MODE_LIST];
static int nummodes;

static qboolean windowed;

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT ret;

    switch(Msg)
    {
        case WM_CLOSE:
            if (MessageBox (NULL, "Are you sure you want to quit?", "Confirm Exit",
                MB_YESNO | MB_SETFOREGROUND | MB_ICONQUESTION) == IDYES) {
                Sys_Quit ();
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            ret = DefWindowProc(hWnd, Msg, wParam, lParam);
    }

    return ret;
}

void VID_InitDIB(HINSTANCE hInstance)
{
    WNDCLASS wc;
    HDC hgdc;
    int i

    wc.style = 0;
    wc.lpfnWndProc = (WNDPROC)MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = 0;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Stupid3DTry";

    if(!RegisterClass(&wc))
        Sys_Error("Couldn't register window class!");

    modelist[0].type = MS_WINDOWED;

    if (COM_CheckParm("-width"))
		modelist[0].width = atoi(com_argv[COM_CheckParm("-width")+1]);
	else
		modelist[0].width = 640;

    if (modelist[0].width < 320)
		modelist[0].width = 320;

    if (COM_CheckParm("-height"))
		modelist[0].height= atoi(com_argv[COM_CheckParm("-height")+1]);
	else
		modelist[0].height = modelist[0].width * 240/320;

	if (modelist[0].height < 240)
		modelist[0].height = 240;

    sprintf (modelist[0].modedesc, "%dx%d",
        modelist[0].width, modelist[0].height);

    modelist[0].modenum = MODE_WINDOWED;
    modelist[0].dib = 1;
    modelist[0].fullscreen = 0;
    modelist[0].halfscreen = 0;
    modelist[0].bpp = 0;

    nummodes = 1;
}

void VID_Init(void)
{
    extern HINSTANCE global_hInstance;

    VID_InitDIB();

    // GL_Init();
}
