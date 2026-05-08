#include <raylib.h>
#include <raymath.h>
#define WIDTH 800
#define HEIGHT 500

int main(void){
    Vector2 center = {
        WIDTH/2 + 100, HEIGHT/2
    };
    float v_a = 2.0f, v_a2 = 4.0f, v_a3 = 8.0f;
 
    float radius = 150.f;
    float angle = 0, angle_2 = 0, angle_3 = 0;
    InitWindow(WIDTH, HEIGHT, "Aceleracao Centripeta");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        Vector2 mouse = GetMousePosition();
        float dt = GetFrameTime();
        if(IsKeyPressed(KEY_R)){
            angle -= v_a * dt;
            angle_2 -= v_a2 * dt;
            angle_3 -= v_a3 * dt;
        } else if (IsKeyPressed(KEY_W)) {
            angle += v_a * dt;
            angle_2 += v_a2 * dt;
            angle_3 += v_a3 * dt;
        }
        angle += v_a * dt;
        angle_2 += v_a2 * dt;
        angle_3 += v_a3 * dt;
        Vector2 pos = {
            center.x + cosf(angle) * (radius + 50),
            center.y + sinf(angle) * (radius + 50)
        };
        Vector2 pos_2 = {
            center.x + cosf(angle_2) * radius,
            center.y + sinf(angle_2) * radius
        };
        Vector2 pos_3 = {
            center.x + cosf(angle_3) * (radius - 70),
            center.y + sinf(angle_3) * (radius - 70)
        };
        Vector2 direcaoCentro = Vector2Subtract(center, pos);
        Vector2 direcaoCentro_2 = Vector2Subtract(center, pos_2);
        Vector2 direcaoCentro_3 = Vector2Subtract(center, pos_3);
        
        Vector2 aceleracaoCentripeta = Vector2Normalize(direcaoCentro); 
        Vector2 aceleracaoCentripeta_2 = Vector2Normalize(direcaoCentro_2);
        Vector2 aceleracaoCentripeta_3 = Vector2Normalize(direcaoCentro_3);
        
        // Multiplicamos por uma escala para visualização
        float distance = sqrtf((center.x - pos.x)*(center.x - pos.x) + (center.y - pos.y)*(center.y - pos.y));
        float distance_2 = sqrtf((center.x - pos_2.x)*(center.x - pos_2.x) + (center.y - pos_2.y)*(center.y - pos_2.y));
        float distance_3 = sqrtf((center.x - pos_3.x)*(center.x - pos_3.x) + (center.y - pos_3.y)*(center.y - pos_3.y));
        
        Vector2 vetorVisual = Vector2Scale(aceleracaoCentripeta, distance);
        Vector2 vetorVisual_2 = Vector2Scale(aceleracaoCentripeta_2, distance_2);
        Vector2 vetorVisual_3 = Vector2Scale(aceleracaoCentripeta_3, distance_3);
        
        float distance_mouse_center = sqrtf((center.x - mouse.x)*(center.x - mouse.x) + (center.y - mouse.y)*(center.y - mouse.y));
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && distance_mouse_center < radius-70) {
            center = (Vector2){mouse.x, mouse.y};
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleLinesV(center, radius, WHITE);
        DrawCircleLinesV(center, radius+50, WHITE);
        DrawCircleLinesV(center, radius-70, WHITE);
        DrawLineEx(
            pos,
            Vector2Add(pos, vetorVisual),
            3.0f, BLUE
            );
        DrawLineEx(
            pos_2,
            Vector2Add(pos_2, vetorVisual_2),
            3.0f, RED
            );
        DrawLineEx(
            pos_3,
            Vector2Add(pos_3, vetorVisual_3),
            3.0f, GREEN
            );
        
        DrawCircleV(pos, 30, BLUE);
        DrawCircleV(pos_2, 20, RED);
        DrawCircleV(pos_3, 10, GREEN);
        DrawCircleV(center, 30, WHITE);
        
        const char* cos_azul = TextFormat("Cosseno(BLUE): %.2f", cosf(angle));
        const char* sin_azul = TextFormat("Sen(BLUE): %.2f", sinf(angle));
        
        const char* cos_red = TextFormat("Cosseno(RED): %.2f", cosf(angle_2));
        const char* sin_red = TextFormat("Sen(RED): %.2f", sinf(angle_2));
        
        const char* cos_green = TextFormat("Cosseno(GREEN): %.2f", cosf(angle_3));
        const char* sin_green = TextFormat("Sen(GREEN): %.2f", sinf(angle_3));
        
        DrawText(sin_azul, 20,20, 20, WHITE);
        DrawText(cos_azul, 20,50, 20, WHITE);
        
        DrawText(cos_red, 20,HEIGHT-100, 20, WHITE);
        DrawText(sin_red, 20,HEIGHT-130, 20, WHITE);
        
        DrawText(cos_green, 20,HEIGHT/2, 20, WHITE);
        DrawText(sin_green, 20,HEIGHT/2-30, 20, WHITE);
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
