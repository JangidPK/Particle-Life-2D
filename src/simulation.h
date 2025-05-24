#ifndef SIMULATION_H
#define SIMULATION_H

#include <particles.h>
#include <vector>
#include "parameters.h"

// Simulation class
class Simulation {
public:
    void run(std::vector<Particle> &particles);
    double Time = 0;
    double T = 1;
    double boxWidth = prm.box_width;
    double boxHeight = prm.box_height;

private:

    // number of steps in the simulation
    int steps = 0;

    // integration time step
    double dt = 0.005;

    // Integrate the particles' positions and velocities using the Velocity Verlet method
    void integrate(std::vector<Particle>& particles, double dt);

    // Handle periodic or reflecting  boundary conditions for particles
    void handleBoundary(Particle& p, double boxWidth, double boxHeight);

    // Calculate the force between two particles using the Lennard-Jones potential
    // Particle Life force (PL)
    void PL(Particle& p1, Particle& p2);
};

#endif // SIMULATION_H