#ifndef GRAVITY_H
#define GRAVITY_H

#include <SFML/Graphics.hpp>
#include "../core/EventHandler.h"
#include "../core/SimulationState.h"
#include "../entities/Mass.h"

struct GravitySettings : public BaseSettings {
    float gravity = 9.8f;
    float airDensity = 1.225f;
    float height = 10.0f;
    float groundRestitution = 0.8;
};

void sceneOne();

#endif