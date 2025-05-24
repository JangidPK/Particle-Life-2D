#ifndef PARTICLES_H
#define PARTICLES_H

#include<random>
#include<array>

struct Particle {
    std::array<double, 3> r;
    std::array<double, 3> v;
    std::array<double, 3> f;
    std::vector<int> neighbors;
    double radius=4, m=1;
    int type;
    int id;
    
    Particle() {        
    }

    void updatePosition(double dt) {
        for (int i = 0; i < 3; i++) {
            this->r[i] += v[i] * dt;
        }
    }

    void setVelocity(double T, int is_zero) {

        std::random_device device;
        std::mt19937 gen(device());
        std::normal_distribution<float> normdist(0, 1);
        
        double scale = sqrt(T / m);
        for (int i = 0; i < 3; i++) {
            this->v[i] = normdist(gen) * scale;
        }
        if (is_zero == true) {
            this->v[0] = 0;
            this->v[1] = 0;
            this->v[2] = 0;
        }
    }

    void setPosition(double LX, double LY) {
        std::random_device device;
        std::mt19937 gen(device());
        std::uniform_real_distribution<double> unidist(0, 1);

        this->r[0] = unidist(gen) * LX;
        this->r[1] = unidist(gen) * LY;
        this->r[2] = 0;
    }

    void getNeighbors(std::vector<Particle>& particles) {
        neighbors.clear();
        for (auto& p : particles) {
            if (this->id != p.id) {
                double dx = this->r[0] - p.r[0];
                double dy = this->r[1] - p.r[1];
                double sigma = (this->radius + p.radius); // LJ parameter
                double cutoff = 3 * sigma; // LJ cutoff distance
                double dist = std::sqrt(dx * dx + dy * dy);
                if (dist < cutoff) {
                    this->neighbors.push_back(p.id);
                }
            }
        }
    }
};

#endif // PARTICLES_H