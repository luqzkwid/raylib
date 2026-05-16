#include <print> //--- C++23
#include <raylib.h>

#define WIDTH  850
#define HEIGHT 500
#define WAVE_COUNT 10
void movement(Vector2& center, Vector2& wave_center, float vel, float& radius);
int
main(void) {
    Vector2 center = {WIDTH/2, HEIGHT/2};
    Vector2 wave_center = center;
    float radius = 20, wave_radius = 0;
    InitWindow(WIDTH, HEIGHT, "Sample_Text");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        movement(center, wave_center, 2.0f, radius);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(center, radius, WHITE);
        float dt = GetFrameTime();
        float wave_space = 20;
        for(int i=1; i <= 3; i++){
            DrawCircleLinesV(wave_center, wave_radius + wave_space, WHITE);
            if(wave_radius >= radius+wave_space){
                wave_radius = 0;
                DrawCircleLinesV(center, wave_radius, WHITE);
            }
            if(i == 3){
                DrawCircleLinesV(wave_center, radius+wave_space, RED);
            }
            wave_radius += 10.0f * dt;
            wave_space  += 20; // 80
        }
        EndDrawing();
    }
    return 0;
};

void movement(Vector2& center, Vector2& wave_center, float vel, float& radius){
    if(IsKeyDown(KEY_W)){
        center.y -= vel;
    };
    if(IsKeyDown(KEY_S)){
        center.y += vel;
    };
    if(IsKeyDown(KEY_A)){
        center.x -= vel;
        wave_center.x = (center.x + 20.0f);
    };
    if(IsKeyDown(KEY_D)){ center.x += vel; };
}
