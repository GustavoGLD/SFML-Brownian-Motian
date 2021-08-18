#include <bits/stdc++.h>
#include <TGUI/TGUI.hpp>
#include "../GLD/GLD.hpp"
#include "random.hpp"

#define PARTICLE_RADIUS 5
#define PARTICLE_VELOC  150

using Random = effolkronium::random_static;

namespace brown
{

class Particle {
public:
    sf::CircleShape* shape = new sf::CircleShape();
    sf::Vector2f veloc;

    void update(GLD::Time time, sf::RenderWindow& window){

        sf::Vector2f new_position;
        new_position.x = shape->getPosition().x + veloc.x * time.getDeltaTime();
        new_position.y = shape->getPosition().y + veloc.y * time.getDeltaTime();
        
        if (new_position.x < 0 || new_position.x > window.getSize().x)
            veloc.x *= -1;
        if (new_position.y < 0 || new_position.y > window.getSize().y)
            veloc.y *= -1;
        
        shape->move(veloc.x * time.getDeltaTime(), veloc.y * time.getDeltaTime());
    }

    ~Particle(){
        delete shape;
    }
};

}

const std::vector<brown::Particle*> genParticles(sf::RenderWindow& window, unsigned int particles_squared)
{
    std::vector<brown::Particle*> new_particles;

    const float window_x = (float)window.getSize().x;
    const float window_y = (float)window.getSize().y;
    const float particle_dist_x = window_x / particles_squared;
    const float particle_dist_y = window_y / particles_squared;

    for (int i = 0; i < particles_squared; i++){

        for (int ii = 0; ii < particles_squared; ii++){

            brown::Particle* new_particle = new brown::Particle();
            new_particle->shape->setRadius(PARTICLE_RADIUS);
            new_particle->shape->setFillColor(sf::Color::Cyan);

            float new_pos_x = window_x - (particle_dist_x * (i  + 1)) + particle_dist_x / 2;
            float new_pos_y = window_y - (particle_dist_y * (ii + 1)) + particle_dist_y / 2;

            new_particle->shape->setPosition({new_pos_x, new_pos_y});

            new_particle->veloc.x = Random::get<float>(-PARTICLE_VELOC, PARTICLE_VELOC);
            new_particle->veloc.y = Random::get<float>(-PARTICLE_VELOC, PARTICLE_VELOC);

            new_particles.push_back(new_particle);
        }
    }

    return new_particles;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "TGUI window", sf::Style::Default);
    tgui::Gui gui(window);

    GLD::Time time;

    auto slider = tgui::Slider::create();
    slider->setSize("20%", "3%");
    slider->setPosition((float)window.getSize().x * (0.5 - 0.1), "5%");
    slider->setValue(5);
    slider->setMinimum(3);
    slider->setMaximum(12);
    gui.add(slider);

    std::vector<brown::Particle*> particles;
    int last_slider_value = -1;
    while (window.isOpen()){
        sf::Event event;
        time.getFrameInit();

        while (window.pollEvent(event)){
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (slider->getValue() != last_slider_value){
            for (auto particle : particles) delete particle;
            particles = genParticles(window, slider->getValue() * 2);
            last_slider_value = slider->getValue();
        }

        window.clear({0, 0, 10});
        for (auto particle : particles){
            particle->update(time, window);
            window.draw(*particle->shape);
        }
        gui.draw();
        window.display();
    }

    return EXIT_SUCCESS;
}