#include "Mass.h"
#include <cmath>
#include <SFML/Graphics.hpp>

Mass::Mass(sf::Vector2f position, float mass, float radius) : position(position), mass(mass), radius(radius) {
    float pixelsPerMeter = 50.0f;
    shape.setRadius(radius);
    shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
    shape.setFillColor(sf::Color::White);
}

void Mass::draw(sf::RenderWindow& window) {
    float pixelsPerMeter = 50.0f;
    shape.setPosition(position * pixelsPerMeter);
    shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
    shape.setRadius(radius * pixelsPerMeter);
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

void Mass::setRadius(float newRadius) {
    radius = newRadius;
    shape.setOrigin(sf::Vector2f(newRadius, newRadius));
}

float Mass::getRadius() {
    return radius;
}

// hardcoded Drag Coefficient for sphere (change later)
sf::Vector2f Mass::calculateDragForce(float airDensity) {
    float speed = std::sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    float speedSquared = speed * speed;

    if (speed < 0.0001f) {
        return sf::Vector2f(0, 0);
    }

    sf::Vector2f direction = velocity / speed;

    float dragMagnitude = (1.0f / 2.0f) * airDensity * speedSquared * (0.47) * (3.14 * (radius * radius));
    sf::Vector2f dragForce = -direction * dragMagnitude;
    return dragForce;
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