#include <Windows.h>
#include <gl/gl.h>
#include <math.h>

#include "c_ray.h"

#define ww 1024
#define wh 512
#define PI 3.14159265358979323846
#define NUM_RAYS 264

float player_angle = 0.0f;
float fov = PI / 2.0f; // 60 degrees field of view
int last_mouse_x = 0;
float sensitivity = 0.003f;

HWND window;
HDC hdc;
HGLRC hrc;

void handle_mouse_movement()
{
    POINT mouse_pos;
    GetCursorPos(&mouse_pos);
    ScreenToClient(window, &mouse_pos);

    int delta_x = mouse_pos.x - last_mouse_x;
    player_angle += (float)delta_x * sensitivity;

    // Нормализация угла
    while (player_angle < 0) player_angle += 2 * PI;
    while (player_angle >= 2 * PI) player_angle -= 2 * PI;

    last_mouse_x = mouse_pos.x;

    // Возвращаем курсор в центр окна
    RECT rect;
    GetClientRect(window, &rect);
    int center_x = rect.right / 2;
    int center_y = rect.bottom / 2;
    POINT center = {center_x, center_y};
    ClientToScreen(window, &center);
    SetCursorPos(center.x, center.y);
    last_mouse_x = center_x;
}


unsigned char test_map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1},
    {1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

Rect player;

void init_player()
{
    player.pos.x = 100;
    player.pos.y = 100;
    player.width = 10;
    player.height = 10;

}

void cast_ray(float angle, float *end_x, float *end_y)
{
    // Нормализуем угол
    while (angle < 0) angle += 2 * PI;
    while (angle >= 2 * PI) angle -= 2 * PI;

    float ray_x = player.pos.x + player.width / 2;
    float ray_y = player.pos.y + player.height / 2;
    float ray_dir_x = cosf(angle);
    float ray_dir_y = sinf(angle);
    float step = 1.0f;

    while (1) {
        ray_x += ray_dir_x * step;
        ray_y += ray_dir_y * step;

        int map_x = (int)ray_x / BLOCK_SIZE;
        int map_y = (int)ray_y / BLOCK_SIZE;

        if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT) {
            break;
        }

        if (test_map[map_y][map_x] == 1) {
            break;
        }
    }

    *end_x = ray_x;
    *end_y = ray_y;
}


void move_player(Rect *player, float angle, float speed)
{
    float dx = cosf(angle) * speed;
    float dy = sinf(angle) * speed;

    int new_x = player->pos.x + (int)dx;
    int new_y = player->pos.y + (int)dy;

    // Проверка коллизий для всех углов игрока
    if (!check_collision(new_x, new_y) &&
        !check_collision(new_x + player->width - 1, new_y) &&
        !check_collision(new_x, new_y + player->height - 1) &&
        !check_collision(new_x + player->width - 1, new_y + player->height - 1))
    {
        player->pos.x = new_x;
        player->pos.y = new_y;
    }
}

void check_keys()
{
    float speed = 2.0f;

    if (GetAsyncKeyState(0x57) & 0x8000) { // W key (forward)
        move_player(&player, player_angle, speed);
    }
    if (GetAsyncKeyState(0x53) & 0x8000) { // S key (backward)
        move_player(&player, player_angle + PI, speed);
    }
    if (GetAsyncKeyState(0x44) & 0x8000) { // D key (strafe right)
        move_player(&player, player_angle + PI/2, speed);
    }
    if (GetAsyncKeyState(0x41) & 0x8000) { // A key (strafe left)
        move_player(&player, player_angle - PI/2, speed);
    }
    if (GetAsyncKeyState(0x51) & 0x8000) { // Q key (rotate left)
        player_angle -= 0.1f;
        if (player_angle < 0) player_angle += 2 * PI;
    }
    if (GetAsyncKeyState(0x45) & 0x8000) { // E key (rotate right)
        player_angle += 0.1f;
        if (player_angle >= 2 * PI) player_angle -= 2 * PI;
    }
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        PostQuitMessage(0);
    }
    Sleep(10);
}
void R_Render(void)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    check_keys();

    // Define fullscreen view area
    int view_width = ww;
    int view_height = wh;
    Rect sky = {{0, 0}, view_width, view_height / 2};
    Rect ground = {{0, view_height / 2}, view_width, view_height / 2};

    r_drawRect(&ground, DOOM_FLOOR);
    r_drawRect(&sky, DOOM_CEILING);

    float ray_angle;
    float end_x, end_y;
    float player_center_x = player.pos.x + player.width / 2;
    float player_center_y = player.pos.y + player.height / 2;

    for (int i = 0; i < NUM_RAYS; i++)
    {
        ray_angle = player_angle - fov / 2 + (fov * i) / NUM_RAYS;
        cast_ray(ray_angle, &end_x, &end_y);

        // Calculate distance to wall (use Euclidean distance)
        float distance = sqrtf((end_x - player_center_x) * (end_x - player_center_x) +
                               (end_y - player_center_y) * (end_y - player_center_y));

        // Apply fish-eye correction
        distance *= cosf(ray_angle - player_angle);

        // Calculate wall height
        float wall_height = (BLOCK_SIZE / distance) * ((view_width / 2) / tanf(fov / 2));

        // Calculate drawing positions
        int wall_top = (view_height / 2) - (wall_height / 2);
        int wall_bottom = (view_height / 2) + (wall_height / 2);

        // Clamp values
        if (wall_top < 0) wall_top = 0;
        if (wall_bottom >= view_height) wall_bottom = view_height - 1;

        // Calculate color based on distance
        float shade = 1.0f - fminf(distance / 500.0f, 0.8f);
        Color wall_color = DOOM_WALL;

        wall_color.r *= shade;
        wall_color.g *= shade;
        wall_color.b *= shade;

        // Draw vertical line for this ray
        int x = i * view_width / NUM_RAYS;
        r_drawLine(x, wall_top, x, wall_bottom, 32.0f, wall_color);
    }

    // Draw crosshair
    int crosshair_size = 10;
    int crosshair_thickness = 2;
    int center_x = view_width / 2;
    int center_y = view_height / 2;

    // Horizontal line
    r_drawLine(center_x - crosshair_size, center_y,
               center_x + crosshair_size, center_y,
               crosshair_thickness, WHITE);

    // Vertical line
    r_drawLine(center_x, center_y - crosshair_size,
               center_x, center_y + crosshair_size,
               crosshair_thickness, WHITE);



    // Draw mini-map
    int map_size = wh / 3;  // Set the size of the mini-map
    Rect mini_map = {{0, 0}, map_size, map_size};
    r_drawRect(&mini_map, BLACK);
    r_drawMap(test_map, &mini_map);

    // Draw player on mini-map
    float scale = (float)map_size / (MAP_WIDTH * BLOCK_SIZE);
    Rect mini_player = {
        {mini_map.pos.x + player.pos.x * scale, mini_map.pos.y + player.pos.y * scale},
        player.width * scale,
        player.height * scale
    };
    r_drawRect(&mini_player, RED);

    // Draw player direction on mini-map
    float dir_length = 20.0f * scale;
    float dir_end_x = mini_player.pos.x + cosf(player_angle) * dir_length;
    float dir_end_y = mini_player.pos.y + sinf(player_angle) * dir_length;
    r_drawLine(mini_player.pos.x, mini_player.pos.y, dir_end_x, dir_end_y, 2.0f, GREEN);
    SwapBuffers(hdc);
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
    glOrtho(0, ww, wh, 0, -1, 1);
}

void GL_Shutdown(void)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);
    ReleaseDC(window, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch(msg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_DESTROY:
        return 0;
    case WM_ACTIVATE:
        if (LOWORD(wparam) != WA_INACTIVE)
        {
            // Захват мыши при активации окна
            SetCapture(hwnd);
            ShowCursor(FALSE);
        }
        else
        {
            ReleaseCapture();
            ShowCursor(TRUE);
        }
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
    init_player();

    RECT rect;
    GetClientRect(window, &rect);
    last_mouse_x = rect.right / 2;

    wcl.lpfnWndProc = WndProc;
    wcl.lpszClassName = "CRayWindow";

    RegisterClassA(&wcl);

    window = CreateWindowExA(0, "CRayWindow", "cray_v0b.exe", WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
    0, 0, ww, wh, 0, 0, 0, 0);

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
            handle_mouse_movement();
            R_Render();
        }
    }

    GL_Shutdown();
    DestroyWindow(window);
    return 0;
}