#include<stdio.h>
#include<raylib.h>
#include<stdlib.h>
#include<time.h>
#define WIDTH 600
#define HEIGHT 400
#define NUM_OF_SQ 10

typedef struct {
  Vector2 position, velocity, size;
  int colision_state;
  Color color;
} Square;

struct vecs {
    Vector2 v1,v2;
};
Square *CreateSquare();
void Collision(Square *squares[]);
void UpdateSquares(Square *squares[]);
void DrawDistanceBetweenSquares(Square* squares[]);


int main() {
  srand(time(NULL));
  Square* squares[NUM_OF_SQ];
  Square* square_struct = (Square*)malloc(sizeof(Square));
  for(int i=0; i < NUM_OF_SQ; ++i){
    square_struct = CreateSquare();
    squares[i] = square_struct;
  }
  InitWindow(WIDTH, HEIGHT, "Some collision in C.");
  SetTargetFPS(60);
  while(!WindowShouldClose()) {
    float dt = GetFrameTime();
    BeginDrawing();
    ClearBackground(BLACK);
    UpdateSquares(squares);
    DrawDistanceBetweenSquares(squares);
    DrawRectangleV(square.position, square.size, square.color);
    EndDrawing();
    Collision(squares);
  }
  free(square_struct);
  return 0;
}
void DrawDistanceBetweenSquares(Square* squares[]) {
    Vector2 start, end;
    for(int j=0; j<NUM_OF_SQ; j++){
        for(int i=j+1; i < NUM_OF_SQ; i++){
            start = (Vector2){squares[j]->position.x + squares[j]->size.x/2, squares[j]->position.y + squares[j]->size.y/2};
	        end = (Vector2){squares[i]->position.x + squares[i]->size.x/2, squares[i]->position.y + squares[i]->size.y/2};
            DrawLineV(start, end, WHITE);
        }
    }
}
Square *CreateSquare() {
  Square *square            = (Square*)malloc(sizeof(Square));
  square->size              = (Vector2){50,50};
  square->position.x        = rand() % (int)(WIDTH - square->size.x)  + 1;
  square->position.y        = rand() % (int)(HEIGHT - square->size.y) + 1;
  square->velocity          = (Vector2){500,500};
  //square->velocity.x        = rand() % 500 + 1;
  //square->velocity.y        = rand() % 500 + 1;
  square->colision_state    = false;
  square->color             = YELLOW;
  //if(square->position.x < WIDTH){}
  printf("\nX:%f\nY:%f\n", square->position.x, square->position.y);
  return square;
}
void UpdateSquares(Square *squares[]) {
  for(int i=0; i < NUM_OF_SQ; i++) {
      squares[i]->position.x += squares[i]->velocity.x*GetFrameTime();
      squares[i]->position.y += squares[i]->velocity.y*GetFrameTime();
      DrawRectangleV(squares[i]->position, squares[i]->size, squares[i]->color);
  }
}
void Collision(Square *squares[]){
  // Usefull calculus
  //float square_px = (float)squares[i]->position.x + squares[i]->size.x;
  //float square_py = (float)squares[i]->position.y + squares[i]->size.y;
  //float square_mx = (float)squares[i]->position.x;
  //float square_my = (float)squares[i]->position.y;
  for(int i=0; i < NUM_OF_SQ; i++){
    // Collision with Window Borders ------
    int gtW, ltW, gtH, ltH; // greater than (gt) | less than (lt)
    gtW = (squares[i]->position.x + squares[i]->size.x >= WIDTH);
    ltW = (squares[i]->position.x <= 0);
    gtH = (squares[i]->position.y + squares[i]->size.y >= HEIGHT);
    ltH = (squares[i]->position.y <= 0);
    if(gtH || ltH) {squares[i]->velocity.y *= -1;}
    if(gtW || ltW) {squares[i]->velocity.x *= -1;}
    // Collision with other squares -------
    for(int j=i+1; j < NUM_OF_SQ; j++) {
      // Collision sides
      squares[i]->color = YELLOW;
      squares[j]->color = BLUE;
      if ((squares[i]->position.x < (squares[j]->position.x + squares[j]->size.x)  &&
	   (squares[i]->position.x + squares[i]->size.x) > squares[j]->position.x) &&
	  (squares[i]->position.y < (squares[j]->position.y + squares[j]->size.y)  &&
	   (squares[i]->position.y + squares[i]->size.y) > squares[j]->position.y)) {
	squares[i]->color = RED;
	squares[j]->color = RED;
      }
    }
  }
}
