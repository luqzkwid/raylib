#include <raylib.h>
#include <math.h>

#define HEIGHT 500
#define WIDHT 600


Rectangle ray = {
  WIDHT/2, HEIGHT/2,
  100,5
};

typedef struct {
  Vector2 position;
  Vector2 velocity;
  float radius;
  Color color;
} Circle;

void CheckMovement(Circle* circle);

void main(){
  InitWindow(WIDHT, HEIGHT, "Tracker ray");
  Circle target = {(Vector2){WIDHT/2+200, HEIGHT/2}, (Vector2){5,5},20, BLUE};
 SetTargetFPS(40); 
  while(!WindowShouldClose()){
  float dx = ray.x - target.position.x;
  float dy = ray.y - target.position.y;
  const char* target_velocity_text_x = TextFormat("Velocity X: %.1f px/f", target.velocity.x);
  const char* target_velocity_text_y = TextFormat("Velocity Y: %.1fpx/f", target.velocity.y);
  float angle = atan2(dy, dx) * RAD2DEG;
    BeginDrawing();
    ClearBackground(BLACK);
      DrawText("Press Space to increase the velocity", 300, 30, 12, BLUE);
      DrawText(target_velocity_text_x, 50, 30, 24, WHITE);
      DrawText(target_velocity_text_y, 50, 54, 24, WHITE);
      DrawRectanglePro(ray, (Vector2){ray.width,ray.height}, angle, BLUE);
      DrawCircleV(target.position, target.radius, target.color);
    EndDrawing();
    CheckMovement(&target);
  }
}

void CheckMovement(Circle* circle) {
  if(IsKeyPressed(KEY_SPACE)) {circle->velocity.x += 0.5;circle->velocity.y += 0.5;}
  if(IsKeyDown(KEY_UP)) {circle->position.y -= circle->velocity.y;}
  if(IsKeyDown(KEY_DOWN)) {circle->position.y += circle->velocity.y;}
  if(IsKeyDown(KEY_RIGHT)) {circle->position.x += circle->velocity.x;}
  if(IsKeyDown(KEY_LEFT)) {circle->position.x -= circle->velocity.x;}
}
