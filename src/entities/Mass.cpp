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

void Mass::update(float deltaTime) {
    velocity += acceleration * deltaTime;   // v = v₀ + at
    position += velocity * deltaTime;       // x = x₀ + vt

    acceleration = sf::Vector2f(0, 0);
}

void Mass::applyForce(sf::Vector2f force) {
    acceleration += force / mass;     // a = f / m
}

float Mass::getMass() {
    return mass;
}