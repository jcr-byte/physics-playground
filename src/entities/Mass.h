#ifndef MASS_H
#define MASS_H

#include <SFML/Graphics.hpp>

class Mass {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;
    sf::CircleShape shape;
    float radius;
public:
    Mass(sf::Vector2f position, float mass, float radius);
    void draw(sf::RenderWindow& window);
    void update(float deltaTime);
    void applyForce(sf::Vector2f force);
    float getMass();
    bool checkGroundCollision(float groundPosition);
    void handleGroundCollision(float groundPosition, float restitution);
};

#endif