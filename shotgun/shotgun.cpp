#include "raylib-cpp.hpp"
#define WIDTH 600
#define HEIGHT 400
#define MAX_AMMO 30
typedef struct {
  Vector2 position;
  Vector2 velocity;
  float radius;
} Circle;

typedef struct {
  Vector2 position, velocity;
  float radius;
  bool IsActive;
} Ammo;
typedef struct {
  Vector2 position, size;
} Gun;
void CheckMovement(Circle* circle);
//Start -- main
int main(void){
  raylib::Window window(WIDTH, HEIGHT, "Shotgun Game");
  Circle player = {(Vector2){WIDTH/2, HEIGHT/2}, (Vector2){5,5}, 20.0f};
  SetTargetFPS(60);
  while(!window.ShouldClose()){
    BeginDrawing();
    Ammo bullet = {{player.position.x+5,player.position.y}, {5,5}, 5 ,true};
    window.ClearBackground(BLACK);
    DrawCircleV(player.position, player.radius, BLUE);

    if (IsKeyDown(KEY_S)) {
      bullet.IsActive = true;
      bullet.position = {player.position.x+5, player.position.y};
    }
    DrawCircleV(bullet.position, bullet.radius, GREEN);
    bullet.position.x += bullet.velocity.x;
    bullet.position.y += bullet.velocity.y;
    
    EndDrawing();
    CheckMovement(&player);
  }  
}
void CheckMovement(Circle* circle) {
  if(IsKeyPressed(KEY_SPACE)) {circle->velocity.x += 0.5;circle->velocity.y += 0.5;}
  if(IsKeyDown(KEY_UP)) {circle->position.y -= circle->velocity.y;}
  if(IsKeyDown(KEY_DOWN)) {circle->position.y += circle->velocity.y;}
  if(IsKeyDown(KEY_RIGHT)) {circle->position.x += circle->velocity.x;}
  if(IsKeyDown(KEY_LEFT)) {circle->position.x -= circle->velocity.x;}
  //  if(IsKeyDown(KEY_K))    {}
}
