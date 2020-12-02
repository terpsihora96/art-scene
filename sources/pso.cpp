#include <random>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <chrono>
#include <thread>
#include "../headers/pso.hpp"
#include "../headers/textures.hpp"
#include "../headers/write.hpp"

#define UP (1.0)
#define LO (0.0)
#define MAX_ITER (30)
#define size (0.9)
#define FUNC(x) (1.0 / (1.0 + exp(-x)))
#define NUM_PARTICLES (85)
#define NUM_MICROSECS (0)

Particle::Particle()
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> p_runif(LO, UP);
   std::uniform_real_distribution<> v_runif(-abs(UP - LO), abs(UP - LO));

   m_position = m_best = p_runif(gen);
   m_velocity = v_runif(gen);
   m_fitness = FUNC(m_position);
}

void Particle::updateVelocity(double velocity)
{
   m_velocity = velocity;
}

void Particle::updatePosition(void)
{
   m_position += m_velocity;
}

void Particle::updateBest(double best)
{
   m_best = best;
}

double Particle::position(void)
{
   return m_position;
}

double Particle::best(void)
{
   return m_best;
}

double Particle::fitness(void)
{
   return m_fitness;
}

double Particle::velocity(void)
{
   return m_velocity;
}

double Particle::acceler_coef(void)
{
   return m_acceler_coef;
}

double Particle::inertia(void)
{
   return m_inertia;
}

PSO::~PSO()
{
   for (auto p : m_swarm)
   {
      delete p;
   }
   free_textures();
}

void PSO::create_population(int population_size)
{
   m_population_size = population_size;
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> runif(LO, UP);
   m_global_best = runif(gen);
   m_swarm.resize(0);

   for (int i = 0; i < population_size; ++i)
   {
      m_swarm.push_back(new Particle());
      if (FUNC(m_swarm[i]->position()) > m_swarm[i]->fitness())
      {
         m_global_best = m_swarm[i]->position();
      }
   }
}

double PSO::start(int param1, double param2)
{
   create_population(NUM_PARTICLES);
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> runif(LO, UP);
   int iter = 0;

   // PSO algorithm
   // In each interation compute particles' fitnesses, their positions, velocities
   // As well as the best solution for the iteration - m_global_best
   while (iter < MAX_ITER)
   {
      for (auto particle : m_swarm)
      {
         // Update velocity
         particle->updateVelocity(
             particle->velocity() * particle->inertia() +
             (particle->acceler_coef() * runif(gen)) * (particle->best() - particle->position()) +
             (particle->acceler_coef() * runif(gen)) * (m_global_best - particle->position()));
         particle->updatePosition();
         // Find local best position
         if (FUNC(-particle->position()) > particle->fitness())
         {
            particle->m_best = particle->position();
            particle->m_fitness = (1.0 / (1.0 + exp(-(particle->position()))));
         }
         // Find global best position
         if ((1.0 / (1.0 + exp(-(m_global_best)))) > particle->fitness())
         {
            m_global_best = particle->position();
         }

         // -----------------------------------
         // Begin animation for this iteration
         // Use calculated results to create an interesting animation

         // CUBE
         glColor3f(0.4, particle->fitness(), abs(particle->position()));
         glTranslatef(1, particle->fitness() / 10, 1 - abs(particle->position()));
         glRotatef(particle->fitness(), 1, particle->fitness(), 1 - abs(particle->position()));
         glutSolidCube(particle->fitness());

         // FAN
         // Change texture randomly in each iteration
         std::srand(static_cast<unsigned int>(std::time(nullptr)));
         int texture = (rand() % NUMBER_OF_TEXTURES);
         // Set randomly chosen texture
         glBindTexture(GL_TEXTURE_2D, texture_names[texture]);
         glNormal3f(0, 1 - particle->fitness(), 1);
         glBegin(GL_TRIANGLE_FAN);
         glTexCoord2f(0, 0);
         glVertex3f(cos(particle->position()) / 2, particle->position() + size / 2, 3);
         glTexCoord2f(0, 128);
         glVertex3f(sin(particle->m_best), particle->position() + size / 2, 4);
         glTexCoord2f(128, 128);
         glVertex3f(sin(particle->position()), particle->position() - size / 2, 2);
         glTexCoord2f(128, 0);
         glVertex3f(sin(particle->fitness() - size / 2), particle->best() + size / 2, 0);
         glEnd();

         // TORUS
         glColor3f(0, 1, abs(particle->position()));
         if (particle->fitness() > 0)
         {
            glutSolidTorus(particle->position() * param1 / 10, particle->fitness() * 6, NUMBER_OF_TEXTURES, 13);
         }
         // WIRE OBJECTS - they add great visual impression, as well as the impression of randomness
         glColor3f(abs(m_global_best) * particle->position(), particle->fitness(), particle->position());
         glutWireCube(abs(particle->position()));
         glutWireTorus(particle->position(), particle->fitness() * 6, NUMBER_OF_TEXTURES, 13);
         glPushMatrix();
         glRotatef(particle->fitness(), m_global_best, 1, 0);
         glScalef(particle->velocity(), 0, 0);
         glutWireCube(abs(particle->position()) * param2);
         glPopMatrix();
         // Draw 0 and + mainly in the lower part of the scene
         glColor3f(0, 1, abs(particle->position()));
         draw_name(std::to_string(0), particle->fitness() * 1000 * m_global_best, particle->best() * 100);
         draw_name("+", 1000 * particle->position(), particle->best() * 100);
      }
      iter++;
   }
   return m_global_best;
}
