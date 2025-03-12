#include "ray.h"
#include <math.h>

#define HUD_HEIGHT 120
#define CIRCLE_RADIUS 30
#define CIRCLE_CENTER_X 50
#define CIRCLE_CENTER_Y (view_height - HUD_HEIGHT / 2)

void r_drawHud()
{
    char buffer[64];
    int base_x = 0;
    int base_y = view_height - HUD_HEIGHT;
    rect_t hud_rect = {.pos={.x=base_x, .y=base_y}, .width=WW, .height=HUD_HEIGHT};

    // Draw HUD background
    r_drawRect(&hud_rect, BLACK);

    // Draw circular angle indicator
    r_drawCircle(CIRCLE_CENTER_X, CIRCLE_CENTER_Y, CIRCLE_RADIUS, RED);

    // Draw angle indicator line
    float angle_x = CIRCLE_CENTER_X + CIRCLE_RADIUS * cosf(player.angle);
    float angle_y = CIRCLE_CENTER_Y + CIRCLE_RADIUS * sinf(player.angle);
    r_drawLine(CIRCLE_CENTER_X, CIRCLE_CENTER_Y, angle_x, angle_y, 1, YELLOW);

    // Draw speed
    snprintf(buffer, sizeof(buffer), "SPEED: %d", (int)(player.speed * 100));
    r_sprint(CIRCLE_CENTER_X * 2 + 10, base_y + 30, buffer, strlen(buffer), GREEN);

    // Draw position
    snprintf(buffer, sizeof(buffer), "X: %d  Y: %d", (int)player.pos.x, (int)player.pos.y);
    r_sprint(CIRCLE_CENTER_X * 2 + 10, base_y + 60, buffer, strlen(buffer), GREEN);

    // Draw health and ammo (placeholder values)
    // snprintf(buffer, sizeof(buffer), "HEALTH: 100%%");
    // r_sprint(WW - 200, base_y + 30, buffer, strlen(buffer), RED);

    // snprintf(buffer, sizeof(buffer), "AMMO: 50");
    // r_sprint(WW - 200, base_y + 60, buffer, strlen(buffer), YELLOW);
}
