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
void UpdateAmmo();
void Draw(Gun* gun, Player* px);
void AddMovement(Player* px, Gun* gun);
void AddEnemies();

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
      UpdateAmmo();
      for(int r=0; r<rounds; r++){
	for(int i=0; i< EnemiesList.size(); i++){
	  if(EnemiesList.at(i).position.y + EnemiesList.at(i).radius > HEIGHT){EnemiesList.at(i).position.y = 0;}
	  if(EnemiesList.at(i).position.x + EnemiesList.at(i).radius > WIDTH ||
	     EnemiesList.at(i).position.y + EnemiesList.at(i).radius > HEIGHT){
	    continue;
	  } else {
	    DrawCircleV(EnemiesList.at(i).position, EnemiesList.at(i).radius, YELLOW);
	    EnemiesList.at(i).position.y += EnemiesList.at(i).velocity.y * 0.2;
	    std::cout << "Enemy: " << i << "\n";
	    std::cout << "X: " << EnemiesList.at(i).position.x << "\n";
	    std::cout << "Y: " << EnemiesList.at(i).position.y << "\n";
	  }
	}
      }
    EndDrawing();
    AddMovement(&p, &gun);
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
