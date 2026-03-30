#include "raylib-cpp.hpp"

#define HEIGHT 600
#define WIDTH 700
void AddMovement(raylib::Camera3D* camera);
int main(void){
  raylib::Window window(WIDTH, HEIGHT, "Hello, ray-cpp");
 
  raylib::Camera3D cam = {};
  cam.position = (raylib::Vector3){0.2f, 1.0f,2.0f};
  cam.target = (raylib::Vector3){0.0f, 2.0f, 0.0f};
  cam.up = (raylib::Vector3){0.0f, 1.0f, 0.0f};
  cam.fovy = 45.0f;
  cam.projection = CAMERA_PERSPECTIVE;
  SetTargetFPS(60); 

  ::Vector3 cube_position = Vector3{ 0.4f, 1.0f, 0.1f };
 while(!window.ShouldClose()) {
    UpdateCamera(&cam, CAMERA_FREE);
    BeginDrawing();
    window.ClearBackground(BLACK);
      BeginMode3D(cam);
      DrawCube(cube_position, 2.0f, 2.0f, 2.0f, RED);
      DrawCubeWires(cube_position, 2.0f, 2.0f, 2.0f, BLUE);
      DrawCube(Vector3{ 0.0f, 0.0f, 0.0f }, 10.0f, 0.05f, 10.5f, GREEN);
      DrawGrid(10, 1.0f);
      EndMode3D();
    EndDrawing();
    AddMovement(&cam);
  }
}
void AddMovement(raylib::Camera3D* camera) {
  if(IsKeyDown(KEY_LEFT_SHIFT)){camera->position.y -= 0.05f;}
  // if(IsKeyDown(KEY_SPACE)){camera->position.y += 0.05f;}
}
