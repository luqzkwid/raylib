#include <print>
#include <raylib.h>
#include <cmath>
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
class Atom {
private:
    float angle, radius, atomic_radius;
    int num_of_electrons, electrons_temp;
    map<int, int> layers;
    map<string, vector<int>> layers_diagnostic;

    map<string, vector<int>>
    diagnostic_layers() {
        map<string, vector<int>>lmap;
        lmap["completed_layers"];
        lmap["incompleted_layer"];
        for(auto& [level, max_electrons] : this->layers){
            if(this->electrons_temp - max_electrons >= 0){
                // Here we have a completed layer!
                this->electrons_temp -= max_electrons;
                lmap["completed_layers"].push_back(level);
            } else {
                lmap["incompleted_layer"].push_back(level);
                break;
            }
        }
        print("INFO: Printing the completed layer vector!\n");
        for(int i=0; i<lmap["completed_layers"].size(); i++){
            print("Layers: {} --- MaxElec.: {}\n",
                  lmap["completed_layers"].at(i),
                  this->layers[lmap["completed_layers"].at(i)]);
        }
        print("INFO: Printing the incompleted layer vector!\n");
        for(int i=0; i<lmap["incompleted_layer"].size(); i++){
            print("Layers: {} -- MaxElec.: {}\n",
                  lmap["incompleted_layer"].at(i),
                  this->layers[lmap["incompleted_layer"].at(i)]);
        }
        return lmap;
    }
public:
    Vector2 center;
    float v_a;
    Atom(int eletrons, float radius, Vector2 center){
        this->center           = center;
        this->num_of_electrons = eletrons;
        this->electrons_temp   = eletrons;
        this->radius           = radius;
        this->v_a              = 0.03f;
        this->angle            = 0;
        this->layers           = map<int, int>{{1, 2},{2, 8},{3, 18},{4, 32},{5, 32},{6, 18},{7, 8}};
        this->layers_diagnostic = diagnostic_layers();
    }
    void draw(){
        float k = 40;
        DrawCircleV(this->center, this->radius, GREEN);
        vector<int> incomp_layer = layers_diagnostic["incompleted_layer"];
        vector<int> comp_layers = layers_diagnostic["completed_layers"];

        for(int i=1; i <= comp_layers.size(); i++) {
            int electrons_count = this->layers[i];
            float space_electron = 20.0f;
            DrawCircleLinesV(this->center, this->radius+k, RAYWHITE);
            for(int j=1; j <= electrons_count; j++){
                Vector2 pos = {
                    this->center.x + cosf(this->angle + space_electron) * (this->radius+k),
                    this->center.y + sinf(this->angle + space_electron) * (this->radius+k)
                };
                DrawCircleV(pos, 8, BLUE);
                space_electron +=10;
            }
            if(i == comp_layers.size()){
                electrons_count = this->electrons_temp;
                const char* electrons = TextFormat("Eletrons: %d", this->electrons_temp);
                DrawText(electrons, this->center.x + this->radius, this->center.y - this->radius, 24, WHITE);
                DrawCircleLinesV(this->center, this->radius+k+40, DARKBLUE);
                for(int a=1; a <= electrons_count; a++){
                    Vector2 pos = {
                        this->center.x + cosf(this->angle + space_electron) * (this->radius+k+40),
                        this->center.y + sinf(this->angle + space_electron) * (this->radius+k+40)
                    };
                    DrawCircleV(pos, 8, BLUE);
                    space_electron+=10;
                    DrawLineV(this->center, pos, WHITE);
                    if(a == electrons_count){
                        float dx, dy;
                        dx = this->center.x - pos.x;
                        dy = this->center.y - pos.y;
                        this->atomic_radius = sqrt((dx*dx) + (dy*dy));
                    }
                }
            }
            this->angle += this->v_a * GetFrameTime();
            k+=this->radius+10;
        }

    }
    void hints(){
        DrawText("Valencia Layer",
                 this->center.x + this->atomic_radius - 70,
                 this->center.y - this->atomic_radius, 24, DARKBLUE);

    };  // HINT

    void enable_controls(){
        if(IsKeyPressed(KEY_D)){
            if(this->radius >= 10){
                this->radius -= 2;
            };
        } else if(IsKeyPressed(KEY_I)){
            if(this->radius <= 40){
                this->radius += 2;
            };
        }
    }
}; // CLASS atom
int
main(void){
    Vector2 center = {WIDTH/2,HEIGHT/2 };
    Atom atom_test = Atom{30, 30, center};
    SetTargetFPS(60);
    InitWindow(WIDTH, HEIGHT, "Atom Simulations");
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_S)){atom_test.v_a   +=   0.02f;}
        if(IsKeyPressed(KEY_D)){atom_test.v_a   -= 0.02f;}

        // if(IsKeyPressed(KEY_J)){atom_test_1.v_a += 0.02f;}
        // if(IsKeyPressed(KEY_K)){atom_test_1.v_a -= 0.02f;}

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){atom_test.center = GetMousePosition();}
        // if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){atom_test_1.center = GetMousePosition();}
        BeginDrawing();

        ClearBackground(BLACK);
        	atom_test.draw();
        	atom_test.hints();
        	atom_test.enable_controls();
        EndDrawing();
    }
    //atom_test.hints();
    return 0;
}
