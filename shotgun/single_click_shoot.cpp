#include "raylib-cpp.hpp"
#include <vector>

#define WIDTH 600
#define HEIGHT 400
typedef struct {
  Vector2 position, velocity;
  float radius;
} Player;
typedef struct {
  Vector2 position, size;
} Gun;

typedef struct {
  Vector2 position,velocity;
  float radius; bool active;
} Bullet;

std::vector<Bullet> BulletList;
void shoot(Gun* gun);
void UpdateAmmo();
void DrawGun(Gun* gun, Player* px);
void AddMovement(Player* px);
// globals
Vector2 p_pos={200,200}, p_vel={5,5};
int main(void){
  raylib::Window window(WIDTH, HEIGHT, "Shotgun Game");
  Player p = {p_pos, p_vel, 20}; // position, velocity, radius
  Gun gun  = {{p_pos.x+10, p_pos.y}, {30, 10}};
  SetTargetFPS(60);
  while(!window.ShouldClose()){
    BeginDrawing();
    window.ClearBackground(BLACK);
    DrawGun(&gun, &p); 
      shoot(&gun);
      AddMovement(&p);
      UpdateAmmo();
      
    EndDrawing();
    
  }
}
void AddMovement(Player* px) {
  if(IsKeyDown(KEY_UP))      {p_pos.y -= p_vel.y;}
  if(IsKeyDown(KEY_DOWN))    {p_pos.y += p_vel.y;}
  if(IsKeyDown(KEY_RIGHT))   {p_pos.x += p_vel.x;}
  if(IsKeyDown(KEY_LEFT))    {p_pos.x -= p_vel.x;}
}
void DrawGun(Gun* gun, Player* pX) {
  DrawCircleV(p_pos, pX->radius, BLUE);
  DrawRectangleV(p_pos, gun->size, RED);
}
void shoot(Gun* gun) {
  if(IsKeyPressed(KEY_SPACE)) {
    Bullet newBullet;
    newBullet.position = {
      p_pos.x + gun->size.x,
      p_pos.y + gun->size.y/2
    };
    newBullet.velocity = {10,0};
    newBullet.radius   = 5;
    newBullet.active   = true;
    
    BulletList.push_back(newBullet);
  }
}
void UpdateAmmo() {
  for(int i=0; i < BulletList.size(); i++) {
    if (BulletList.at(i).active) {
      DrawCircleV(BulletList.at(i).position, BulletList.at(i).radius, GREEN );
      BulletList.at(i).position.x += BulletList.at(i).velocity.x;
      BulletList.at(i).position.y += BulletList.at(i).velocity.y;
    }
    if(BulletList.at(i).position.x > GetScreenWidth() ||
       BulletList.at(i).position.y > GetScreenHeight()) {

      BulletList.at(i).active = false;
    }
  }
}
