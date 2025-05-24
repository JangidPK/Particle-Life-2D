#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <array>
#include <random>
#include <SFML/Graphics.hpp>


struct Parameters {
    static constexpr int num_type = 3;

    int num_particles = 200; // per type

    double box_width = 1820;
    double box_height = 900;

    std::array<sf::Color, 6> colors = {
        sf::Color(231, 76, 60),   // Red
        sf::Color(46, 204, 113),  // Green
        sf::Color(52, 152, 219),  // Blue
        sf::Color(241, 196, 15),  // Yellow
        sf::Color(155, 89, 182),  // Purple
        sf::Color(26, 188, 156)   // Teal
    };


    std::array<std::array<double, num_type>, num_type> forcefield{};
    std::array<std::array<double, num_type>, num_type> min_dist{};
    std::array<std::array<double, num_type>, num_type> radius{};

    Parameters() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> unidist(0.0, 1.0);

        for (int i = 0; i < num_type; i++) {
            for (int j = 0; j < num_type; j++) {
                forcefield[i][j] =  100*(0.3 + unidist(gen) * 0.7);

                // ramdonly assign positive or negative forcefield
                if (unidist(gen) < 0.5) {
                    forcefield[i][j] *= -1;
                }
                min_dist[i][j] = 10 + unidist(gen) * 20;
                radius[i][j] = 40 + unidist(gen) * 100;
            }

        }
    }
};

// Declare the global variable (only declare here)
extern Parameters prm;

#endif
