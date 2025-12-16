#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/EventHandler.h"
#include "entities/Mass.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Window");

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