#include <raylib.h>
#include <stdlib.h>
#define WIDTH 800
#define HEIGHT 450
typedef struct {
    Vector2 pos, s, vel;
    Color color;
} Rect;
typedef struct {
    Vector2 center, vel;
    float radius;
    Color color;
} Ball;
int Collision(Ball* b, Rect* rect_1, Rect* rect_2);
void movement_logic(Rect* rect_1, Rect* rect_2, Ball* b);
void make(Rect* rect_1, Rect* rect_2, Ball* b);
void endgame(int rc, Ball* b);

int
main(void){
    int x = 800;
    int y = 450;

    Rect rect_1;
    Rect rect_2;
    Ball b;

    int game_over = 0;
    SetTargetFPS(60);
    InitWindow(x,y, "Seeing physics");
    make(&rect_1, &rect_2, &b);
    while(!WindowShouldClose()){
        float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);
          int text_width_rect_2 = MeasureText("Player 2", 20);
          DrawText("Player 1", rect_1.pos.x, rect_1.pos.y - 25, 20, WHITE);
          DrawText("Player 2", rect_2.pos.x - text_width_rect_2/2, rect_2.pos.y - 25, 20, WHITE);
          DrawRectangleV(rect_1.pos, rect_1.s, WHITE);
          DrawRectangleV(rect_2.pos, rect_2.s, WHITE);
          DrawCircleV(b.center, b.radius, b.color);
          game_over = Collision(&b, &rect_1, &rect_2);
          if(game_over == -1){
              b.vel = (Vector2){0,0};
              const char* endgame_message = "", play_again_message = "Wanna play again? (Press R)";
              int font_endgame = 50, font_playagain = 25;

              if(b.center.x > WIDTH/2)     { endgame_message = "Player 2 Loose";}
              else if(b.center.x < WIDTH/2){ endgame_message = "Player 1 Loose";}

              int text_witdh_endgame = MeasureText(endgame_message, font_endgame);
              int text_width_play_again = MeasureText(play_again_message, font_playagain);

              DrawText(
              endgame_message,
              WIDTH/2 - text_witdh_endgame/2,
              HEIGHT/2 - font_endgame,
              font_endgame,
              WHITE);

              DrawText(
              play_again_message,
              WIDTH/2 - text_width_play_again/2,
              HEIGHT/2,
              font_playagain,
              WHITE);
              if(IsKeyPressed(KEY_R)){
                  game_over = 0;
              }
          }
          EndDrawing();
    }
}
int
Collision(Ball *b, Rect* rect_1, Rect* rect_2){
    float dt = GetFrameTime();
    movement_logic(rect_1, rect_2, b);
    // Collision ball-rect
    if(CheckCollisionCircleRec(b->center,b->radius,
    (Rectangle){rect_1->pos.x, rect_1->pos.y, rect_1->s.x, rect_1->s.y})) {
        b->vel.x *= -1.1;
    }
    if(CheckCollisionCircleRec(b->center,b->radius,
    (Rectangle){rect_2->pos.x, rect_2->pos.y, rect_2->s.x, rect_2->s.y}))
    {
        b->vel.x *= -1.1;
    }
    // Game Over Collision
    if(b->center.x + b->radius >= WIDTH){
        b->center.x = WIDTH - b->radius; b->vel.x *= -1;
        return -1;
    }
    else if(b->center.x - b->radius <= 0){
        b->center.x = b->radius; b->vel.x *= -1;
        return -1;
    }
    else if(b->center.y + b->radius >= HEIGHT){
        b->center.y = HEIGHT - b->radius; b->vel.y *= -1;
    }
    else if(b->center.y - b->radius <= 0){
        b->center.y = b->radius; b->vel.y *= -1;
    }
};
void
movement_logic(Rect* rect_1, Rect* rect_2, Ball* b){
    // Movement Rect_2
    if(IsKeyDown(KEY_UP))  {rect_2->pos.y -= rect_2->vel.y * GetFrameTime();}
    if(IsKeyDown(KEY_DOWN)){rect_2->pos.y += rect_2->vel.y * GetFrameTime();}
    // Movement Rect_1
    if(IsKeyDown(KEY_W)){rect_1->pos.y -= rect_1->vel.y * GetFrameTime();}
    if(IsKeyDown(KEY_S)){rect_1->pos.y += rect_1->vel.y * GetFrameTime();}
    // Ball movement
    b->center.x += (b->vel.x * GetFrameTime());
    b->center.y += (b->vel.y * GetFrameTime());
}
void
make(Rect* rect_1, Rect* rect_2, Ball* b) {
    rect_1->s   = (Vector2){30, 200};
    rect_1->pos = (Vector2){30, HEIGHT/2 - rect_1->s.y/2 };
    rect_1->vel = (Vector2){300, 300};

    rect_2->s = (Vector2){30, 200};
    rect_2->pos = (Vector2){WIDTH - 60, HEIGHT/2 - rect_2->s.y/2};
    rect_2->vel = (Vector2){300, 300};
    // --------
    b->center = (Vector2){WIDTH/2,HEIGHT/2};
    b->vel = (Vector2){500,500};
    b->radius = 10; b->color = YELLOW;
}
void endgame(int rc, Ball* b){
    if(rc == -1) {
        DrawText("YOU LOOSE BABY", WIDTH/2 - 50, HEIGHT/2 - 50, 50, WHITE);
        b->vel = (Vector2){0,0};
    }
}
