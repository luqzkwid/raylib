#include <raylib.h>
#define WIDTH  850
#define HEIGHT 500
int
main(void){
    InitWindow(WIDTH, HEIGHT, "Snake");
    SetTargetFPS(60);
    int board[WIDTH * HEIGHT];
    int cellsize = 30; // px X px;
    Vector2 startpos_cols = {100, 100};
    Vector2 endpos_cols = {100,HEIGHT};
    
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        for(int cols=cellsize; cols > HEIGHT/cellsize; cols++){
            DrawLineV(startpos_cols, endpos_cols, WHITE);
        }
        DrawLineV(startpos_cols, endpos_cols, WHITE);
        EndDrawing();
    }                           
}
