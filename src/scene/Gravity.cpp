#include <SFML/Graphics.hpp>
#include "../core/EventHandler.h"
#include "../entities/Mass.h"

void sceneOne() {

    sf::VertexArray ground(sf::PrimitiveType::Lines, 2);
    ground[0].position = sf::Vector2f(0.f, 500.f);
    ground[1].position = sf::Vector2f(800.f, 500.f);
    ground[0].color = sf::Color::White;
    ground[1].color = sf::Color::White;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Window");

    EventHandler eventHandler;

    Mass mainMass(sf::Vector2f(0, 0), 3, 20);

    while (window.isOpen()) {
        if (eventHandler.processEvents(window)){
            window.close();
        }

        window.clear();

        mainMass.draw(window);
        window.draw(ground);

        window.display();
    }

}