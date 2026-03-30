#include "raylib-cpp.hpp"
#include <vector>
#include <random>
// Constants
#define WIDTH 600
#define HEIGHT 400
#define NUMBER_OF_PARTICLES 30
// Particle definition 
typedef struct {
  raylib::Vector2 position, velocity;
  float radius;
} Particle;
// Functions
void DrawParticles(std::vector<Particle> particles);
std::vector<Particle> CreateParticles(int number_of_particles, float radius);
void Colision(std::vector<Particle>& particles);
// Start
int main(void) {
  raylib::Window window(WIDTH, HEIGHT, "Collsion Particles");
  std::vector<Particle> particles = CreateParticles(NUMBER_OF_PARTICLES, 10); // Initializate Particles (CreateParticles function)
  SetTargetFPS(120);
  while(!window.ShouldClose()) {
    BeginDrawing();
    window.ClearBackground(BLACK);
    // Loop over the particles vector and Draw a Circle for each particle
    DrawParticles(particles);
     // Implementing Velocity for each particle in the vector
    for(int particle=0; particle<NUMBER_OF_PARTICLES; particle++){
      particles.at(particle).position.x += particles.at(particle).velocity.x;
      particles.at(particle).position.y += particles.at(particle).velocity.y;
    }
    EndDrawing();
    Colision(particles); // Add colision (receive particles vector in the parameter)
  }
  return 0;
}

void Colision(std::vector<Particle>& particles) {
  for(int particle=0; particle<particles.size(); particle++){
    if(particles.at(particle).position.x + particles.at(particle).radius > WIDTH)   {particles.at(particle).velocity.x *= -1;}
    if(particles.at(particle).position.y + particles.at(particle).radius > HEIGHT)  {particles.at(particle).velocity.y *= -1;}
    if(particles.at(particle).position.y - particles.at(particle).radius < 0)       {particles.at(particle).velocity.y *= -1;}
    if(particles.at(particle).position.x - particles.at(particle).radius < 0)       {particles.at(particle).velocity.x *= -1;}
  }
}
std::vector<Particle> CreateParticles(int number_of_particles, float radius){
  std::vector<Particle> particles; //
  std::random_device rd; //         Rendering random numbers.
  std::mt19937 gen(rd()); //
  for(int i=0; i<number_of_particles; i++){  
    std::uniform_int_distribution<> distrib_velocity(-10, 10); // random number starting FROM -10 TO 10
    std::uniform_int_distribution<> distrib_position_y(radius, WIDTH-radius); // random number starting FROM particle radius TO WIDTH - particle radius
    std::uniform_int_distribution<> distrib_position_x(radius, HEIGHT-radius); // random number starting FROM particle radius TO HEIGHT - particle radius
    Particle particle;
    particle.radius = radius;
    particle.position.y = (float)distrib_position_y(gen); //
    particle.position.x = (float)distrib_position_x(gen); // Inserting the random values 
    particle.velocity.x = (float)distrib_velocity(gen); //
    particle.velocity.y = (float)distrib_velocity(gen); // 
    
    particles.push_back(particle); // Adding the particles to the vector
  }
  return particles; // returning the vector with the particles on it
}

void DrawParticles(std::vector<Particle> particles) {
  // Loop every particle in the particles vector and Draw a Circle for each one
  for(int i=0; i<particles.size(); i++){
    DrawCircleV(particles[i].position, particles[i].radius, GREEN);
  }
}
