#include "EventHandler.h"

bool EventHandler::processEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            return true;
        }
    }
    return false;
}