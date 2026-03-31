#include <iostream>

#include "raylib-cpp.hpp"
#include <vector>
#include <random>

#define WIDTH 600
#define HEIGHT 400
#define NUMBER_OF_ENEMIES 20

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
typedef struct {
  Vector2 position,velocity;
  float radius; int health;
} Enemy;
// Globals
Vector2 p_pos={200,200}, p_vel={5,5};
std::vector<Enemy> EnemiesList;
std::vector<Bullet> BulletList;
// Functions Definitions
void shoot(Gun* gun);
// void UpdateAmmo();
void Draw(Gun* gun, Player* px);
void AddMovement(Player* px, Gun* gun);
void AddEnemies();
// void UpdateEnemies();
void Update();
int main(void){
  raylib::Window window(WIDTH, HEIGHT, "Shotgun Game");
  Player p = {p_pos, p_vel, 20}; // position, velocity, radius
  Gun gun  = {{p_pos.x+10, p_pos.y}, {50, 5}, 0.0f};
  int rounds = 5;
  AddEnemies();
  SetTargetFPS(60);
  while(!window.ShouldClose()){
    shoot(&gun);
    BeginDrawing();
    window.ClearBackground(BLACK);
      Draw(&gun, &p); 
      Update();
      AddMovement(&p, &gun);
    EndDrawing();
  }
}
void AddEnemies(){
  std::random_device rd; //         Rendering random numbers.
  std::mt19937 gen(rd()); //
  for(int i=0; i < NUMBER_OF_ENEMIES; i++){
    std::uniform_int_distribution<> distrib_velocity_x_above(0, 0);
    std::uniform_int_distribution<> distrib_velocity_y_above(1, 1); 
    std::uniform_int_distribution<> distrib_position_y_above(-100, -10); 
    std::uniform_int_distribution<> distrib_position_x_above(0, WIDTH);

    Enemy enemy_above;
    enemy_above.position.x = (float)distrib_position_x_above(gen);
    enemy_above.position.y = (float)distrib_position_y_above(gen);
    enemy_above.velocity.x = (float)distrib_velocity_x_above(gen);
    enemy_above.velocity.y = (float)distrib_velocity_y_above(gen);
    enemy_above.radius     = 10;
    enemy_above.health     = 100;

    EnemiesList.push_back(enemy_above);
  }
}
void AddMovement(Player* px, Gun* gun) {
  Vector2 mouse = GetMousePosition();
  float dx    = mouse.x - p_pos.x;
  float dy    = mouse.y - p_pos.y;
  float angle = atan2f(dy, dx) * (180.0f / PI);
  gun->aov = angle;
  
  if(IsKeyDown(KEY_W))   {p_pos.y -= p_vel.y;}
  if(IsKeyDown(KEY_S)) {p_pos.y += p_vel.y;}
  if(IsKeyDown(KEY_D)){p_pos.x += p_vel.x;}
  if(IsKeyDown(KEY_A)) {p_pos.x -= p_vel.x;}
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
void Update() {
  // Loop into enemies vector and if the Ammo colides with the enemy surface, then we stop drawing enemy
  bool colide_with_bullet = false;
  for(int i=0; i<EnemiesList.size(); i++){
    for(int j=0; j< BulletList.size(); j++){
      float dx = EnemiesList.at(i).position.x - BulletList.at(j).position.x;
      float dy = EnemiesList.at(i).position.y - BulletList.at(j).position.y;
      float radius_sum = EnemiesList.at(i).radius + BulletList.at(j).radius;

      if(dx*dx + dy*dy <= radius_sum * radius_sum) {
	colide_with_bullet = true;
	BulletList.at(j).active = false;
      }
      if (BulletList.at(j).active) {
	DrawCircleV(BulletList.at(j).position, BulletList.at(j).radius, GREEN );
	BulletList.at(j).position.x += BulletList.at(j).velocity.x;
	BulletList.at(j).position.y += BulletList.at(j).velocity.y;
      }
      if(BulletList.at(j).position.x > GetScreenWidth() ||
	 BulletList.at(j).position.y > GetScreenHeight()) {
	BulletList.at(j).active = false;
      }
    } // Here ends the bullet for loop
    if (EnemiesList.at(i).position.y + EnemiesList.at(i).radius > HEIGHT ||
	EnemiesList.at(i).position.x + EnemiesList.at(i).radius > WIDTH) {EnemiesList.at(i).position.y = 0;}
    if (!colide_with_bullet) {												 
      DrawCircleV(EnemiesList.at(i).position, EnemiesList.at(i).radius, YELLOW);				 
      EnemiesList.at(i).position.y += EnemiesList.at(i).velocity.y * 0.9;					 
      std::cout << "Enemy: " << i << "\n";								 
      std::cout << "X: " << EnemiesList.at(i).position.x << "\n";						 
      std::cout << "Y: " << EnemiesList.at(i).position.y << "\n";						 
    } else {
      DrawCircleV(EnemiesList.at(i).position, EnemiesList.at(i).radius, RED);
      continue;
    }
  }
}
/* 
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
  for(int i=0; i< EnemiesList.size(); i++){
    if (EnemiesList.at(i).position.y + EnemiesList.at(i).radius > HEIGHT ||
	EnemiesList.at(i).position.x + EnemiesList.at(i).radius > WIDTH) {EnemiesList.at(i).position.y = 0;}
    if () {												 
      DrawCircleV(EnemiesList.at(i).position, EnemiesList.at(i).radius, YELLOW);				 
      EnemiesList.at(i).position.y += EnemiesList.at(i).velocity.y * 0.9;					 
      std::cout << "Enemy: " << i << "\n";								 
      std::cout << "X: " << EnemiesList.at(i).position.x << "\n";						 
      std::cout << "Y: " << EnemiesList.at(i).position.y << "\n";						 
    }
    }*/												 
