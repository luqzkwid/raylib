#include <print>
#include <sstream>
#include <raylib.h>
#include <cmath>
#include "lof.hpp"
#include <string>
#include <vector>
#include <map>
/***
**WARNING (for emacs users): for read this, consider disabling the whitespace-mode if it is enabled (Or set to not mark tabs for better reading). And be sure to compile this program with c++23 **

I start with the idea of each layer must have sublevels,
which accept a specific amount of electrons. But the sublevels is the less important
part for this Simple Atom Simulation, so i only considers the amount
of electrons. For example, we have this separation ->
                    Layers --------- Electrons Max cap.
                    1 (K)  --------- 2
                    2 (L)  --------- 8
                    3 (M)  --------- 18
                    4 (N)  --------- 32
                    5 (O)  --------- 32
                    6 (P)  --------- 18
                    7 (Q)  --------- 8
So following this idea, if i receive 32 electron from input, i should distribute then
in a more convinient way than the original one (Electronic Distribution).
---- TODO: Implement a way to receive X amount of electrons as input, and distribut then to the layers.

***/
using std::print;
using std::map;
using std::vector;
using std::string;
// using std::
#define WIDTH  850
#define HEIGHT 500
#define ANGLE_FACTOR 360
Logger lof{Logger::LogLevelError};
class Atom {
 private:
    float angle;
    float radius;
    int num_of_electrons;
    map<int, int> layers;
    map<string, vector<int>> layers_diagnostic;

    map<string, vector<int>> diagnostic_layers() {
        map<string, vector<int>>lmap;
        lmap["completed_layers"];
        lmap["incompleted_layers"];
        for(auto& [level, max_electrons] : this->layers){
            if(this->num_of_electrons - max_electrons >= 0){
                // Here we have a completed layer!
                this->num_of_electrons -= max_electrons;
                lmap["completed_layers"].push_back(level);
            } else {
                lmap["incompleted_layers"].push_back(level);
                break;
            }
        }
        return lmap;
    }
public:
    Vector2 center;
    float v_a;
    Atom(int eletrons, float radius, Vector2 center){
        this->center           = center;
        this->num_of_electrons = eletrons;
        this->radius           = radius;
        this->v_a              = 0.03f;
        this->angle            = 0;
        this->layers           = map<int, int>{{1, 2},{2, 8},{3, 18},{4, 32},{5, 32},{6, 18},{7, 8}};
        this->layers_diagnostic = diagnostic_layers();
    }
    void draw(){
        float k = 40;
        DrawCircleV(this->center, this->radius, YELLOW);
        for(int i=1; i <= layers_diagnostic["completed_layers"].size(); i++) {
            int electrons_count = this->layers[i];
            float space_eletron = 20;
        }
    }
};
int
main(void){
    Vector2 center = {WIDTH/2,HEIGHT/2};
    Atom atom_test = Atom{35, 20, center};
    SetTargetFPS(60);
    InitWindow(WIDTH, HEIGHT, "Atom Simulations");
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_W)){atom_test.v_a += 0.002f;}
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){atom_test.center = GetMousePosition();}
        BeginDrawing();
        ClearBackground(BLACK);
        atom_test.draw();
        EndDrawing();
    }
    return 0;
}
