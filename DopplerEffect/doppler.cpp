#include <print> //--- C++23
#include <vector>
#include <raylib.h>

using std::print;
using std::vector;

#define WIDTH  1000
#define HEIGHT 650
#define MAX_WAVES 56
#define WAVE_VEL 1.0f
#define WAVE_FREQUENCY 0.2f
#define BODY_VEL 50.0f
typedef struct {
    Color primary;
    Color secondary;
} Colors;
typedef struct {
    Vector2 position;
    float vel;
    float radius;
} SoundWave;
class Body {
private:
    Vector2 position;
    Colors body_colors;
    float vel;
    float interval = 0;
    void create_waves(){
        if(this->waves.size() >= MAX_WAVES){
            print("Max waves reached!!\n");
            this->waves.erase(std::remove_if(
                    this->waves.begin(),
                    this->waves.end(),
                    [](const SoundWave &w){
                        print("Cleaning the waves that gone...");
                        return w.radius >= HEIGHT + 50.0f;}));
        /* Lambda that returns if the wave gets (w.radius >= HEIGHT+ 50) */
        }
        SoundWave new_wave = { this->position, 100.0f, 0 };
        this->waves.push_back(new_wave);
        print("Wave added. Count: {}.\n", this->waves.size());
    } //CREATE_WAVES}

public:
    float radius;
    vector<SoundWave> waves;
    Body(Vector2 pos, float radius, float vel, Colors colors){
        this->position              = pos;
        this->radius                = radius;
        this->vel                   = vel;
        this->body_colors.primary   = colors.primary;
        this->body_colors.secondary = colors.secondary;
    }; //CONSTRUCTOR


    void draw(){
        // TODO(12:34): Do some interval to separate the waves
        float dt = GetFrameTime();
        move_center(dt);
        this->interval += GetFrameTime();
        if(this->interval >= (float)WAVE_FREQUENCY){
            this->interval = 0.0f;
            create_waves();
        }
        for(auto& actual_wave : this->waves){
                actual_wave.radius += actual_wave.vel * dt;
                DrawCircleLinesV(actual_wave.position, actual_wave.radius, this->body_colors.secondary);
        }
        DrawCircleV(this->position, this->radius, this->body_colors.primary);
    }; //DRAW
    void move_center(float dt) {
        if(IsKeyDown(KEY_A)){
            this->position.x -= (float)BODY_VEL * dt;
        }
        if(IsKeyDown(KEY_D)){
            this->position.x += (float)BODY_VEL * dt;
        }
        if(IsKeyDown(KEY_W)){
            this->position.y -= (float)BODY_VEL * dt;
        }
        if(IsKeyDown(KEY_S)){
            this->position.y += (float)BODY_VEL * dt;
        }
    }
}; // CLASS BODY
int
main(void) {
    Vector2 pos = {WIDTH/2, HEIGHT/2};
    Body body = {pos, 20, 0.09f, {GREEN, WHITE}};
    InitWindow(WIDTH, HEIGHT, "Doppler Effect");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        body.draw();
        EndDrawing();
    }
    return 0;
}
