
#include <simulation.h>
#include <iostream>


void Simulation::PL(Particle& p1, Particle& p2){
    /* 
    Function calculates the force applied on particles p1 and p2
    by each other 
    prm is the parameters object that contains the forcefield,
    min_dist and radius arrays
    p1 and p2 are the two particles that are interacting
    The function first calculates the distance between the two particles
    and checks if it is less than the radius of the two particles.
    If it is, it calculates the force applied on each particle
    by the other particle and updates the force vector of each particle
    */
    
    double dx = p1.r[0] - p2.r[0];
    double dy = p1.r[1] - p2.r[1];
    double r2 = dx * dx + dy * dy;
    // double dist = std::sqrt(r2);

    // apply the periodic boundary condition
    if (dx > boxWidth / 2) dx -= boxWidth;
    else if (dx < -boxWidth / 2) dx += boxWidth;
    if (dy > boxHeight / 2) dy -= boxHeight;
    else if (dy < -boxHeight / 2) dy += boxHeight;
    double dist = std::sqrt(dx * dx + dy * dy);

    double scale_rep, scale_att, force;

    if ( dist < prm.radius[p1.type][p2.type]){
        
        // calculate the long range force 
        // force is attactive if the forcefield is positive
        // and repulsive if the forcefield is negative

        scale_att = prm.forcefield[p1.type][p2.type]/prm.radius[p1.type][p2.type];
        
        force =  -scale_att * (prm.min_dist[p1.type][p2.type] - dist);  
        
        // set the repulsion force to zero
        scale_rep = 0;

        // if the particle is in repulsion range
        // calculate the repulsion force
        // repusive force is always negatice
        

        if (dist < prm.min_dist[p1.type][p2.type]){
            // repulsive force is 7 time the attractive 
            scale_rep = 7 * abs(prm.forcefield[p1.type][p2.type])/prm.min_dist[p1.type][p2.type];
            //slope * (r[r < mindist] - mindist)
            force -= scale_rep * (dist - prm.min_dist[p1.type][p2.type]);
        
        }
        
        p1.f[0] += force * dx / dist;
        p1.f[1] += force * dy / dist;

    }

    if ( dist < prm.radius[p2.type][p1.type]){
        
        // calculate the long range force 
        // force is attactive if the forcefield is positive
        // and repulsive if the forcefield is negative

        scale_att = prm.forcefield[p2.type][p1.type]/prm.radius[p2.type][p1.type];
        
        force =  -scale_att * (prm.min_dist[p2.type][p1.type] - dist);  
        
        // set the repulsion force to zero
        scale_rep = 0;

        // if the particle is in repulsion range
        // calculate the repulsion force
        // repusive force is always negatice

        if (dist < prm.min_dist[p2.type][p1.type]){

            scale_rep = 7 * abs(prm.forcefield[p2.type][p1.type])/prm.min_dist[p2.type][p1.type];
            //slope * (r[r < mindist] - mindist)
            force -= scale_rep * (dist - prm.min_dist[p2.type][p1.type]);
        
        }
        
        dx = -dx; // reverse the direction of the force
        dy = -dy; // reverse the direction of the force
        p2.f[0] += force * dx / dist;
        p2.f[1] += force * dy / dist;
    }
}

void Simulation::integrate(std::vector<Particle>& particles, double dt) {
    
    // reset the forces on all particles
    for (auto& particle : particles) {
        particle.f[0] = 0;
        particle.f[1] = 0;
    }

    for (int i = 0; i < particles.size(); i++){

        // calculate the force on particle i by all other particles
        for (int j = i+1; j < particles.size(); j++){
            if (particles[i].id != particles[j].id){
                PL(particles[i], particles[j]);
            }
        }

        //update the velocity of the particle
        handleBoundary(particles[i], boxWidth, boxHeight);
        particles[i].v[0] += particles[i].f[0] * dt / particles[i].m;
        particles[i].v[1] += particles[i].f[1] * dt / particles[i].m ;

        // damp the velocity
        particles[i].v[0] *= 0.99;
        particles[i].v[1] *= 0.99;

        // update the position of the particle
        particles[i].r[0] += particles[i].v[0] * dt + 0.5 * particles[i].f[0] * dt * dt / particles[i].m;
        particles[i].r[1] += particles[i].v[1] * dt + 0.5 * particles[i].f[1] * dt * dt / particles[i].m;
    }

    steps++;
    Time = steps * dt;
}

// reflecting boundary
// void Simulation::handleBoundary(Particle& p, double Lx, double Ly) {
//     if (p.r[0] - p.radius < 0) {
//         p.r[0] = p.radius;
//         p.v[0] = -p.v[0];
//     } else if (p.r[0] + p.radius > Lx) {
//         p.r[0] = Lx - p.radius;
//         p.v[0] = -p.v[0];
//     }

//     if (p.r[1] - p.radius < 0) {
//         p.r[1] = p.radius;
//         p.v[1] = -p.v[1];
//     } else if (p.r[1] + p.radius > Ly) {
//         p.r[1] = Ly - p.radius;
//         p.v[1] = -p.v[1];
//     }
// }



// Periodic Boundary
void Simulation::handleBoundary(Particle& p, double Lx, double Ly) {
    if (p.r[0] < 0) p.r[0] += Lx;
    if (p.r[0] >= Lx) p.r[0] -= Lx;
    if (p.r[1] < 0) p.r[1] += Ly;
    if (p.r[1] >= Ly) p.r[1] -= Ly;
}


void Simulation::run(std::vector<Particle> & particles) {
    for (uint16_t runs = 0; runs < 5; runs++){
        for (int i = 0; i < 1; i++){
            integrate(particles, dt);
        }
    }
}   

