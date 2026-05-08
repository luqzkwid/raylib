#include <print>
#include <sstream>
#include <raylib.h>

#include "lof.hpp"

using std::print;
// using std::
#define WIDTH  850
#define HEIGHT 500
// LOF initialization ---- Log Of Freaking
Logger lof{Logger::LogLevelError};

class Atom {
private:
    Vector2 center;
    int layers;
    int num_of_eletrons;
    double radius;
public:
    Atom(int layers, int eletrons, float radius){
        center = Vector2{WIDTH/2, HEIGHT/2};
        this->num_of_eletrons = eletrons;
        this->layers          = layers;
        this->radius          = radius;

        std::stringstream ss;
        if(this->layers > 8){
            ss << " Current Number of Layers: " << this->layers << "\n";
            lof.err("Maximun Number of Layers (8) reached!" + ss.str());
            ss.str("");
            exit(-1);
            return;
        } else if(this->num_of_eletrons > 10){
            ss << " Number of Eletrons: " << this->num_of_eletrons << "\n";
            lof.err("Maximun Number Of Eletrons (10) reached!" + ss.str());
            ss.str("");
            exit(-1);
            return;
        }
    }
    void draw(){
        float factor_radius = 20;
        DrawCircleV(this->center, this->radius, YELLOW);
        // Draw Each layer
        for(int x=0; x < this->layers; x++){
            DrawCircleLinesV(this->center, this->radius + factor_radius, WHITE);
            factor_radius += 20;
        }
    }
};

int
main(void){
    Atom atom_test = Atom{5, 11, 20};
    InitWindow(WIDTH, HEIGHT, "Atom Simulations");
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
          atom_test.draw();
        EndDrawing();
    }
    return 0;
}
