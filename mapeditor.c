#include <Windows.h>
#include <gl/gl.h>
#include <stdlib.h>
#include <stdio.h>

#include "c_ray.h"

HWND window;
HDC hdc;
HGLRC hrc;



// 32x32
#define WW  512
#define WH  512

unsigned char map[MAP_HEIGHT][MAP_WIDTH] = {0};


void save_map(void)
{
    FILE *file = fopen("map.map", "wb");
    if (file) {
        fwrite(map, sizeof(unsigned char), MAP_WIDTH * MAP_HEIGHT, file);
        fclose(file);
    }
}


void R_Render(void)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    load_map(map);
    glBegin(GL_QUADS);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == 1) {
                glColor3f(1.0f, 1.0f, 1.0f); // White for walls
            } else {
                glColor3f(0.2f, 0.2f, 0.2f); // Dark gray for empty cells
            }
            glVertex2i(x * BLOCK_SIZE, y * BLOCK_SIZE);
            glVertex2i((x + 1) * BLOCK_SIZE, y * BLOCK_SIZE);
            glVertex2i((x + 1) * BLOCK_SIZE, (y + 1) * BLOCK_SIZE);
            glVertex2i(x * BLOCK_SIZE, (y + 1) * BLOCK_SIZE);
        }
    }
    glEnd();

    // Draw grid
    glColor3f(0.5f, 0.5f, 0.5f); // Gray for grid
    glBegin(GL_LINES);
    for (int i = 0; i <= MAP_WIDTH; i++) {
        glVertex2i(i * BLOCK_SIZE, 0);
        glVertex2i(i * BLOCK_SIZE, MAP_HEIGHT * BLOCK_SIZE);
    }
    for (int i = 0; i <= MAP_HEIGHT; i++) {
        glVertex2i(0, i * BLOCK_SIZE);
        glVertex2i(MAP_WIDTH * BLOCK_SIZE, i * BLOCK_SIZE);
    }
    glEnd();

    SwapBuffers(hdc);
}

void HandleMouseClick(int x, int y)
{
    int mapX = x / BLOCK_SIZE;
    int mapY = y / BLOCK_SIZE;

    if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT) {
        map[mapY][mapX] = !map[mapY][mapX];
    }
}
void GL_Init(void)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    hdc = GetDC(window);
    memset(&pfd, 0, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(hdc, &pfd);

    SetPixelFormat(hdc, iFormat, &pfd);

    hrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hrc);
    glOrtho(0, WW, WH, 0, -1, 1);
}

void GL_Shutdown(void)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);
    ReleaseDC(window, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch(msg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_DESTROY:
            return 0;
        case WM_LBUTTONDOWN:
            HandleMouseClick(LOWORD(lparam), HIWORD(lparam));
            break;
        case WM_KEYDOWN:
            if (wparam == 'S' || wparam == 's')
                save_map();
            break;
        default:
            return DefWindowProcA(hwnd, msg, wparam, lparam);
    }
    return 0;
}

int main()
{
    WNDCLASSA    wcl;
    memset(&wcl, 0, sizeof(wcl));

    wcl.lpfnWndProc = WndProc;
    wcl.lpszClassName = "MapEditorWindow";

    RegisterClassA(&wcl);

    window = CreateWindowExA(0, "MapEditorWindow", "MapEditor_v0b.exe", WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
    0, 0, WW, WH, 0, 0, 0, 0);

    GL_Init();
    ShowWindow(window, SW_SHOWNORMAL);

    unsigned char running = 1;
    MSG msg;

    while(running) {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if(msg.message == WM_QUIT)
                running = 0;
            else {
                DispatchMessage(&msg);
                TranslateMessage(&msg);
            }
        } else {
            R_Render();
        }
    }
    GL_Shutdown();
    DestroyWindow(window);
    return 0;
}