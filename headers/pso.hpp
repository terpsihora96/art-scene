#ifndef _PSO_HPP_
#define _PSO_HPP_

#include <vector>

struct Color {
	float r, g, b, a;
	Color(float r = 1, float g = 0, float b = 0, float a = 1) : r(r), g(g), b(b), a(a) {}
};

class Particle {
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
        const double m_acceler_coef = 1.49618;
        // TODO vary inertia (w) from 0.9 to 0.4 over time
        const double m_inertia = 0.7298; 
};

class PSO {
    public:
        PSO() {}
        ~PSO();
        void create_population(int);
        double start();

    private:
        int m_population_size;
        std::vector<Particle*> m_swarm;
        double m_global_best;
};

#endif
