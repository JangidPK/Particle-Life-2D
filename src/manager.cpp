#include <cmath>
#include <manager.h>

Manager::Manager(){
    this->initWindow();
}

Manager::~Manager(){
    delete this->window;
}

const bool Manager::running() const {
    return this->window->isOpen();
}

void Manager::initWindow(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    const uint32_t window_width  = simulation.boxWidth;
    const uint32_t window_height = simulation.boxHeight;
    this->window = new sf::RenderWindow(sf::VideoMode(window_width,window_height),
                                        "Particle Simulation",
                                        sf::Style::Close,
                                        settings);
    this->window->setFramerateLimit(60);

    double id = 0;
    for (int i = 0; i < prm.num_particles; i++){
        for (int type = 0; type < prm.num_type; type++){
            spawnParticle(type, id);
        }
        id++;
    }
}

void Manager::render(){
    
    this->window->clear(sf::Color(60,60,60,0));
    // render the objects
    for (auto it = particleSFList.begin(); it != particleSFList.end(); it++){
        this->window->draw(**it);
    }
    textdisplay->draw(*window);
    timedisplay->draw(*window);
    energydisplay->draw(*window);

    this->window->display();
}

void Manager::update(){
    this->pollEvents();

    textdisplay->setText( "Particle Number : " + std::to_string(particles.size()));
    timedisplay->setText( "Time  : " + std::to_string(simulation.Time));
    energydisplay->setText( "Particle types : " + std::to_string(prm.num_type));

    // update the particles
    simulation.run(particles);
   
    // update the particle positions to render
    for (int i = 0; i < particleSFList.size(); i++){
        particleSFList[i]->setPosition(sf::Vector2f(particles[i].r[0]-particles[i].radius,
                                                    particles[i].r[1]-particles[i].radius));
    }
}

void Manager::pollEvents(){

    while (this->window->pollEvent(this->event)){
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if(this->event.key.code == sf::Keyboard::Escape)
            this->window->close();
            break;
        }
    }
}

void Manager::spawnParticle(int particle_type, int id){
    Particle p;
    p.type = particle_type;
    p.id = id;
    p.setVelocity(simulation.T, 0);
    p.setPosition(simulation.boxWidth, simulation.boxHeight);

    sf::CircleShape *particleSF = new sf::CircleShape(p.radius);

    particleSF->setFillColor(prm.colors[particle_type]);

    particleSFList.push_back(particleSF);

    particles.push_back(p);
}
