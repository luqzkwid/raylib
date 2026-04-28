#include <raylib.h>
#define WIDTH 800
#define HEIGHT 450
// --------
typedef struct {
    Vector2 pos, s, vel;
    Color color;
} Rect;
typedef struct {
    Vector2 center, vel;
    float radius;
    Color color;
} Ball;
// --------
int Collision(Ball* b, Rect* rect_1, Rect* rect_2);
// --------
int main(void){
    int x = 800;
    int y = 450;
    // --------
    Rect rect_1;
    rect_1.s   = (Vector2){30, 200};
    rect_1.pos = (Vector2){30, HEIGHT/2 - rect_1.s.y/2 };
    rect_1.vel = (Vector2){300, 300};
    // --------
    Rect rect_2;
    rect_2.s = (Vector2){30, 200};
    rect_2.pos = (Vector2){WIDTH - 60, HEIGHT/2 - rect_2.s.y/2};
    rect_2.vel = (Vector2){300, 300};
    // --------
    Ball b;
    b.center = (Vector2){WIDTH/2,HEIGHT/2};
    b.vel = (Vector2){500,500};
    b.radius = 10; b.color = YELLOW;

    SetTargetFPS(60);
    InitWindow(x,y, "Seeing physics");
    while(!WindowShouldClose()){
        float dt = GetFrameTime();
        // Rect_1 movement --------
        if(IsKeyDown(KEY_W)){rect_1.pos.y -= rect_1.vel.y * GetFrameTime(); }
        if(IsKeyDown(KEY_S)){rect_1.pos.y += rect_1.vel.y * GetFrameTime(); }
        // Rect_2 movement --------
        if(IsKeyDown(KEY_UP)){rect_2.pos.y -= rect_2.vel.y * GetFrameTime(); }
        if(IsKeyDown(KEY_DOWN)){rect_2.pos.y += rect_2.vel.y * GetFrameTime(); }
        // Ball movement --------
        b.center.x += b.vel.x * dt;
        b.center.y += b.vel.y * dt;
        // --------
        BeginDrawing();
        ClearBackground(RED);
          DrawRectangleV(rect_1.pos, rect_1.s, WHITE);
          DrawRectangleV(rect_2.pos, rect_2.s, WHITE);
          DrawCircleV(b.center, b.radius, b.color);
          Collision(&b, &rect_1, &rect_2);
        EndDrawing();
    }
}
int Collision(Ball *b, Rect* rect_1, Rect* rect_2){
    float dt = GetFrameTime();
    // Collision ball-rect
    if(CheckCollisionCircleRec(b->center,
    b->radius,
    (Rectangle){rect_1->pos.x, rect_1->pos.y, rect_1->s.x, rect_1->s.y})) {
        b->vel.x *= -1.1;
    }
    if(CheckCollisionCircleRec(b->center,
    b->radius,
    (Rectangle){rect_2->pos.x, rect_2->pos.y, rect_2->s.x, rect_2->s.y})) {
        b->vel.x *= -1.1;
    }
    // Game Over Collision
    if(b->center.x + b->radius > WIDTH)       { b->center.x = WIDTH - b->radius; b->vel.x *= -1; }
    else if(b->center.x - b->radius < 0)      { b->center.x = b->radius; b->vel.x *= -1;         }
    else if(b->center.y + b->radius > HEIGHT) { b->center.y = HEIGHT - b->radius; b->vel.y *= -1;}
    else if(b->center.y - b->radius < 0)      { b->center.y = b->radius; b->vel.y *= -1;         }
};
