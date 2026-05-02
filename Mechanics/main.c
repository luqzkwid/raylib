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
        
        float dt = GetFrameTime();
        angle += v_a * dt;
        angle_2 += v_a2 * dt;
        angle_3 += v_a3 * dt;
        Vector2 pos = {
            center.x + cosf(angle) * 200,
            center.y + sinf(angle) * 200
        };
        Vector2 pos_2 = {
            center.x + cosf(angle_2) * radius,
            center.y + sinf(angle_2) * radius
        };
        Vector2 pos_3 = {
            center.x + cosf(angle_3) * 80,
            center.y + sinf(angle_3) * 80
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
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleLinesV(center, radius, WHITE);
        DrawCircleLinesV(center, 200, WHITE);
        DrawCircleLinesV(center, 80, WHITE);
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
        DrawCircleV(center, 50, WHITE);
        
        const char* cos_azul = TextFormat("Cosseno(Azul): %.2f", cosf(angle));
        const char* sin_azul = TextFormat("Sen(Azul): %.2f", sinf(angle));
        
        const char* cos_red = TextFormat("Cosseno(Vermelho): %.2f", cosf(angle + 1.0f));
        const char* sin_red = TextFormat("Sen(Vermelho): %.2f", sinf(angle + 1.0f));
        
        DrawText(cos_azul, 20,20, 20, WHITE);
        DrawText(sin_azul, 20,40, 20, WHITE);
        
        DrawText(cos_red, 20,HEIGHT-100, 20, WHITE);
        DrawText(sin_red, 20,HEIGHT-120, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
