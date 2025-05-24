#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <particles.h>
#include <simulation.h>
#include <text.h>

class Manager{
    public:
    Manager();
        virtual ~Manager();
        void update();
        void render();
        const bool running() const;
        std::vector <Particle> particles;
        Parameters prm;
    private:
        sf::RenderWindow* window;
        sf::Event event;
        void initWindow();
        void pollEvents();
        void spawnParticle(int particle_type, int id);

        Simulation simulation;
        

        Text* textdisplay = new Text("../fonts/Monospace.ttf", "Hello",
                                15, {20, 20});
        Text* timedisplay = new Text("../fonts/Monospace.ttf", "Hello",
                                15, {20, 40});
        Text* energydisplay = new Text("../fonts/Monospace.ttf", "Hello",
                                15, {20, 60});

        std::vector <sf::Shape*> particleSFList;

};

#endif // MANAGER_H
