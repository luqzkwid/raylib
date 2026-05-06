#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#define WIDTH 800
#define HEIGHT 500

void draw_pendulum(float lenght, Vector2 startPos, float angle){
    float thickness = 2.0f;
    Vector2 endPos;
    endPos.x = startPos.x + lenght * sinf(angle);
    endPos.y = startPos.y + lenght * cosf(angle);
    DrawLineEx(startPos, endPos, thickness, WHITE);
    DrawCircleV(endPos, 10, YELLOW);
    return;
};
int
main(void){
    InitWindow(WIDTH, HEIGHT, "Pendulum");
    SetTargetFPS(60);
    Vector2 start = (Vector2){WIDTH/2, 0};
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        draw_pendulum(150, start, 10*DEG2RAD);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
