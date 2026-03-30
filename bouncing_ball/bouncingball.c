#include "raylib.h"

#define WIDTH 600
#define HEIGHT 400

typedef struct {
  float radius;
  Vector2 position;
  Vector2 velocity;
  Color color;
} Ball; // Defines a Ball struct with a vector2 for position and velocity

void Colision(Ball* ball);
void main() {
  InitWindow(WIDTH, HEIGHT, "Bouncing Ball"); 	
  Ball test_ball = {20.0, {50, 150}, {5,5}, BLUE}; // Creating the Ball
  float gravity = 9.8; // simple gravity value

	SetTargetFPS(60);
	while(!WindowShouldClose()){
	  float dt = GetFrameTime(); // Numero abaixo de 0!
	  // Implementing gravity
	  // Start Drawing
	  BeginDrawing();
	  ClearBackground(BLACK);
	  DrawCircleV(test_ball.position, test_ball.radius, test_ball.color);
	  Vector2 mouse = GetMousePosition();
	  // distancex (mouse_x to center_of_circle_X) = (mouse.x - test_ball.position.x)2
	  // distancey (mouse_x to center_of_circle_Y) = (mouse.y - test_ball.position.y)2
	  float dx = mouse.x - test_ball.position.x;
	  float dy = mouse.y - test_ball.position.y;
	  // Mouse grep the ball if the position of the mouse is equal or less than the radius of the ball
	  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (dx * dx) + (dy *dy) <= (test_ball.radius * test_ball.radius))   {
	    test_ball.position = mouse; // ball follows the mouse
	    test_ball.velocity = (Vector2){0, 0}; // when ball follows the mouse, velocity = 0; ( x and y )
	  } else {
	    test_ball.velocity.y += 500 * dt; // Add simple gravity to the ball (just apply a force to the ground)
	    test_ball.position.y += test_ball.velocity.y * dt; //
	  }
	  // Mapping the keys to move the ball (Arrow keys)
	  if(IsKeyDown(KEY_LEFT)){ test_ball.position.x -= 10; } // Left
	  if(IsKeyDown(KEY_UP)){ test_ball.position.y -= 10; } // Up
	  if(IsKeyDown(KEY_DOWN)){ test_ball.position.y += 10; } // Down
	  if(IsKeyDown(KEY_RIGHT)){ test_ball.position.x += 10; } // Right
	  if(IsKeyPressed(KEY_SPACE)){ test_ball.position.y -= 15; } // Jump (it do the same thing as the up key, but with a little more of power)
	  EndDrawing();
	  Colision(&test_ball);
	}
}

void Colision(Ball* ball){
  // Adding colision to the ball, and multiplying the velocity x and y for -0.6 (to make the ball lose velocity each colision)
  if(ball->position.x >= WIDTH - ball->radius) {
    ball->position.x = WIDTH - ball->radius;  // colision
    ball->velocity.y *= -0.6f;                // -velocity
  }
  else if(ball->position.x <= ball->radius){
    ball->position.x = ball->radius;          // colision
    ball->velocity.y *= -0.6f;                // -velocity
  }
  if(ball->position.y >= HEIGHT - ball->radius){
    ball->position.y = HEIGHT - ball->radius; // colision
    ball->velocity.y *= -0.6f;                // -velocity
  }
  else if(ball->position.y <= ball->radius){
    ball->position.y = ball->radius;          // colision
    ball->velocity.y *= -0.6f;                // -velocity
  }
}

