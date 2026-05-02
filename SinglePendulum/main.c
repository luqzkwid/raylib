#include <stdio.h>
#include <raylib.h>
#define WIDTH 800
#define HEIGHT 500

int
main(void){
    InitWindow(WIDTH, HEIGHT, "Pendulum");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
