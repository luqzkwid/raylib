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
  float aov; // angle of vision 
} Gun;
typedef struct {
  Vector2 position,velocity;
  float radius; bool active;
} Bullet;
// Globals
Vector2 p_pos={200,200}, p_vel={5,5};
// Functions Definitions
std::vector<Bullet> BulletList;
void shoot(Gun* gun);
void UpdateAmmo();
void Draw(Gun* gun, Player* px);
void AddMovement(Player* px, Gun* gun);

int main(void){
  raylib::Window window(WIDTH, HEIGHT, "Shotgun Game");
  Player p = {p_pos, p_vel, 20}; // position, velocity, radius
  Gun gun  = {{p_pos.x+10, p_pos.y}, {50, 5}, 0.0f};
  SetTargetFPS(60);
  while(!window.ShouldClose()){
    BeginDrawing();
    window.ClearBackground(BLACK);
    Draw(&gun, &p); 
      shoot(&gun);
      AddMovement(&p, &gun);
      UpdateAmmo();
      
    EndDrawing();    
  }
}
void AddMovement(Player* px, Gun* gun) {
  if(IsKeyDown(KEY_UP)){
    p_pos.y -= p_vel.y;
    gun->aov = -90;
  }
  if(IsKeyDown(KEY_DOWN)){
    p_pos.y += p_vel.y;
    gun->aov = 90;
  }
  if(IsKeyDown(KEY_RIGHT)){
    p_pos.x += p_vel.x;
    gun->aov = 0.0f;
  }
  if(IsKeyDown(KEY_LEFT)){
    p_pos.x -= p_vel.x;
    gun->aov = 180.0f;
  }
}
void Draw(Gun* gun, Player* pX) {
  raylib::Rectangle Gun_template(p_pos.x, p_pos.y, gun->size.x, gun->size.y);
  Vector2 CenterOfOrigin = {0, Gun_template.height/2};
  DrawCircleV(p_pos, pX->radius, BLUE);
  DrawRectanglePro(Gun_template, CenterOfOrigin, gun->aov,  BLUE);
}
void shoot(Gun* gun) {
  if(IsKeyPressed(KEY_SPACE)) {
    Bullet newBullet;
    float radians = gun->aov * (PI / 180.0f);
    float bulletSpeed = 10.0f;
    float gunLength = gun->size.x;
    
    // 2. Calculate spawn position at the tip of the barrel
    // We start at p_pos and move 'gunLength' distance in the gun's direction
    newBullet.position.x = p_pos.x + cosf(radians) * gunLength;
    newBullet.position.y = p_pos.y + sinf(radians) * gunLength;
    
    // 3. Calculate velocity based on angle
    newBullet.velocity.x = cosf(radians) * bulletSpeed;
    newBullet.velocity.y = sinf(radians) * bulletSpeed;
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
