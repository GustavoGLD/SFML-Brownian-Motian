#include <bits/stdc++.h>
#include <TGUI/TGUI.hpp>

#define PARTICLE_RADIUS    5

std::vector<sf::CircleShape*> genParticles(sf::RenderWindow& window, unsigned int particles_squared)
{
    std::vector<sf::CircleShape*> new_particles;

    const float window_x = (float)window.getSize().x;
    const float window_y = (float)window.getSize().y;
    const float particle_dist_x = window_x / particles_squared;
    const float particle_dist_y = window_y / particles_squared;

    for (int i = 0; i < particles_squared; i++){

        for (int ii = 0; ii < particles_squared; ii++){

            sf::CircleShape* new_particle = new sf::CircleShape();
            new_particle->setRadius(PARTICLE_RADIUS);
            new_particle->setFillColor(sf::Color::Cyan);

            float new_pos_x = window_x - (particle_dist_x * (i  + 1)) + particle_dist_x / 2;
            float new_pos_y = window_y - (particle_dist_y * (ii + 1)) + particle_dist_y / 2;

            new_particle->setPosition({new_pos_x, new_pos_y});

            new_particles.push_back(new_particle);
        }
    }

    return new_particles;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "TGUI window", sf::Style::Default);
    tgui::Gui gui(window);

    auto slider = tgui::Slider::create();
    slider->setSize("20%", "3%");
    slider->setPosition((float)window.getSize().x * (0.5 - 0.1), "5%");
    slider->setValue(5);
    slider->setMinimum(3);
    slider->setMaximum(10);
    gui.add(slider);

    std::vector<sf::CircleShape*> particles;
    int last_slider_value = -1;
    while (window.isOpen()){
        sf::Event event;

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
        for (auto particle : particles) 
            window.draw(*particle);
        gui.draw();
        window.display();
    }

    return EXIT_SUCCESS;
}