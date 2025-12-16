#include "Mass.h"
#include <SFML/Graphics.hpp>

Mass::Mass(sf::Vector2f position, float mass, float radius) : position(position), mass(mass) {
    shape.setRadius(radius);
    shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
    shape.setFillColor(sf::Color::White);
}

void Mass::draw(sf::RenderWindow& window) {
    shape.setPosition(position);
    window.draw(shape);
}