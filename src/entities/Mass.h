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
    float restitution;
public:
    Mass(sf::Vector2f position, float mass, float radius, float restitution);
    void draw(sf::RenderWindow& window);
    void update(float deltaTime);
    void applyForce(sf::Vector2f force);
    float getMass();
    void setMass(float newMass);
    float getHeight();
    void setHeight(float newHeight);
    sf::Vector2f getVelocity();
    void setVelocity(sf::Vector2f newVelocity);
    sf::Vector2f getPosition();
    void setRadius(float newRadius);
    float getRadius();
    void setRestitution(float newRestitution);
    float getRestitution();
    sf::Vector2f calculateDragForce(float airDensity);
    bool checkGroundCollision(float groundPosition);
    void handleGroundCollision(float groundPosition, float restitution);

};

#endif