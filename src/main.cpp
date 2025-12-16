#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/EventHandler.h"
#include "entities/Mass.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Window");

    const sf::Font font("/System/Library/Fonts/Helvetica.ttc");
    sf::Text text(font, "Hello SFML", 50);

    sf::CircleShape circle(50.0f);
    circle.setFillColor(sf::Color::Red);
    circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));

    sf::Vector2u windowSize = window.getSize();
    circle.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));

    EventHandler eventHandler;

    Mass mainMass(sf::Vector2f(0, 0), 3, 20);

    
    while (window.isOpen()) {
        if (eventHandler.processEvents(window)){
            window.close();
        }

        window.clear();

        mainMass.draw(window);

        window.display();
    }
}