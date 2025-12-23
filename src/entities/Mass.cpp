#include "Mass.h"
#include <SFML/Graphics.hpp>

Mass::Mass(sf::Vector2f position, float mass, float radius) : position(position), mass(mass), radius(radius) {
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

void Mass::setMass(float newMass) {
    mass = newMass;
}

float Mass::getHeight() {
    return position.y;
}

void Mass::setHeight(float newHeight) {
    position.y = newHeight;
}

sf::Vector2f Mass::getVelocity() {
    return velocity;
}

void Mass::setVelocity(sf::Vector2f newVelocity) {
    velocity = newVelocity;
}

sf::Vector2f Mass::getPosition() {
    return position;
}

bool Mass::checkGroundCollision(float groundPosition) {
    if (position.y + radius >= groundPosition) return true;
    return false;
}

void Mass::handleGroundCollision(float groundPosition, float restitution) {
    bool isCollision = checkGroundCollision(groundPosition);
    if (isCollision) {
        position.y = groundPosition - radius;
        velocity.y = -1 * velocity.y * restitution;
    }
}