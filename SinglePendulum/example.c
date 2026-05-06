// pendulo_raylib.c
// Simulação gráfica de um pêndulo simples usando RK4 e raylib
#include "raylib.h"
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Parâmetros
const double g = 9.80665;
double L = 200.0;        // comprimento (pixels)
double b = 0.0;          // amortecimento (viscous)
double scale = 1.0;      // fator de escala para conversão comprimento->pixels (já aplicado)
double originX, originY; // ponto de suspensão (pixels)

// Estado: theta (rad), omega (rad/s)
typedef struct { double theta, omega; } State;

void derivs(double t, const State *x, State *dxdt) {
    dxdt->theta = x->omega;
    dxdt->omega = - (g / (L/100.0)) * sin(x->theta) - b * x->omega;
    // Observação: convertendo L (pixels) para metros roughly dividindo por 100 para preservar g
}

void rk4_step(double *t, State *x, double dt) {
    State k1, k2, k3, k4, xtmp;

    derivs(*t, x, &k1);

    xtmp.theta = x->theta + 0.5 * dt * k1.theta;
    xtmp.omega = x->omega + 0.5 * dt * k1.omega;
    derivs(*t + 0.5*dt, &xtmp, &k2);

    xtmp.theta = x->theta + 0.5 * dt * k2.theta;
    xtmp.omega = x->omega + 0.5 * dt * k2.omega;
    derivs(*t + 0.5*dt, &xtmp, &k3);

    xtmp.theta = x->theta + dt * k3.theta;
    xtmp.omega = x->omega + dt * k3.omega;
    derivs(*t + dt, &xtmp, &k4);

    x->theta += (dt/6.0) * (k1.theta + 2.0*k2.theta + 2.0*k3.theta + k4.theta);
    x->omega += (dt/6.0) * (k1.omega + 2.0*k2.omega + 2.0*k3.omega + k4.omega);

    *t += dt;
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Pêndulo simples - raylib");
    SetTargetFPS(60);

    originX = screenWidth/2.0;
    originY = 100.0;

    // Estado inicial
    State x = { 30.0 * M_PI / 180.0, 0.0 }; // 30 graus
    double t = 0.0;
    double dt = 1.0/120.0; // passo de integração (s) — usaremos sub-steps para estabilidade

    bool dragging = false;

    while (!WindowShouldClose()) {
        // input: arrastar massa com mouse para definir ângulo
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // se clicar perto do pêndulo, começar arraste
            double bobX = originX + L * sin(x.theta);
            double bobY = originY + L * cos(x.theta);
            double dx = mouse.x - bobX, dy = mouse.y - bobY;
            if (sqrt(dx*dx + dy*dy) < 20.0) dragging = true;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragging = false;
        if (dragging) {
            double dx = mouse.x - originX;
            double dy = mouse.y - originY;
            x.theta = atan2(dx, dy); // atan2(x,y) para ângulo relativo à vertical
            x.omega = 0.0;
        }

        // Simulação: vários subpassos por frame
        int substeps = 4;
        for (int i = 0; i < substeps; i++) rk4_step(&t, &x, dt / substeps);

        // Desenho
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // origem
        DrawCircleV((Vector2){originX, originY}, 5, BLACK);

        // posição da massa
        double bobX = originX + L * sin(x.theta);
        double bobY = originY + L * cos(x.theta);

        // corda
        DrawLineEx((Vector2){originX, originY}, (Vector2){(float)bobX, (float)bobY}, 2.0f, DARKGRAY);

        // massa
        DrawCircle((int)bobX, (int)bobY, 16, MAROON);
        DrawCircleLines((int)bobX, (int)bobY, 16, BLACK);

        // HUD simples
        char buf[128];
        sprintf(buf, "theta = %.2f deg", x.theta * 180.0 / M_PI);
        DrawText(buf, 10, 10, 20, DARKGRAY);
        sprintf(buf, "omega = %.3f rad/s", x.omega);
        DrawText(buf, 10, 34, 20, DARKGRAY);
        DrawText("Click and drag bob to set angle. Keys: +/- length, D toggle damping", 10, screenHeight-24, 12, GRAY);

        EndDrawing();

        // controles simples
        if (IsKeyPressed(KEY_KP_ADD) || IsKeyPressed(KEY_EQUAL)) L += 10.0;
        if (IsKeyPressed(KEY_KP_SUBTRACT) || IsKeyPressed(KEY_MINUS)) L = fmax(20.0, L - 10.0);
        if (IsKeyPressed(KEY_D)) b = (b>0.0) ? 0.0 : 0.5;
    }

    CloseWindow();
    return 0;
}
