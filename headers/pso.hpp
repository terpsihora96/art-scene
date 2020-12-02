#ifndef _PSO_HPP_
#define _PSO_HPP_

#include <vector>

class Particle
{
    friend class PSO;

public:
    Particle();
    void updateVelocity(double);
    void updatePosition(void);
    void updateBest(double);

    double position(void);
    double best(void);
    double fitness(void);
    double velocity(void);
    double acceler_coef(void);
    double inertia(void);

private:
    double m_position;
    double m_best;
    double m_fitness;
    double m_velocity;
    // The best values for this constants according to algorithm
    const double m_acceler_coef = 1.49618;
    const double m_inertia = 0.7298;
};

class PSO
{
public:
    PSO() {}
    ~PSO();
    void create_population(int);
    // param1 and param2 come from main display function
    // They are controlled by user
    double start(int param1, double param2);

private:
    int m_population_size;
    std::vector<Particle *> m_swarm;
    double m_global_best;
};

#endif
