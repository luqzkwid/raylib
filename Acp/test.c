#include "raylib.h"
#include <math.h>

int main(void) {
    // Configurações iniciais
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Pêndulo Simples - Raylib");

    // Parâmetros do Pêndulo
    Vector2 origin = { screenWidth / 2.0f, 50.0f }; // Ponto de fixação
    float length = 300.0f;                         // Comprimento da corda
    float amplitude = 0*DEG2RAD;                        // Ângulo inicial (em radianos)
    float speed = 5.0f;                            // Velocidade da oscilação

    SetTargetFPS(60);
    Vector2 ballPos = {
        
    };
    while (!WindowShouldClose()) {
        // 1. Atualizar: Calcular o ângulo baseado no tempo decorrido
        float time = GetTime(); 
        float angle = amplitude * cos(speed * time);
        ballPos.x = origin.x + length * sin(angle);
        ballPos.y = origin.y + length * cos(angle);
        // 2. Calcular a posição (x, y) da bola usando trigonometria
        // Somamos à origem para que o pêndulo fique centralizado
        
        Vector2 mouse = GetMousePosition();
        float ball_radius = 20;
        float dx = mouse.x - ballPos.x;
        float dy = mouse.y - ballPos.y;
        float distance = (dx*dx) + (dy*dy);
        if(distance < ball_radius*ball_radius){
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                ballPos = mouse;
                speed = 0;
            }
        }
        // 3. Desenhar
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // Desenha a corda
            DrawLineV(origin, ballPos, BLACK);
            
            // Desenha a "massa" do pêndulo
            DrawCircleV(ballPos, 20, MAROON);

            DrawText("Pêndulo Simples em C", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
