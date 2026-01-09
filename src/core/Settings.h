#ifndef SETTINGS_H
#define SETTINGS_H

struct SimulationSettings {
    bool isPaused = true;
    float pixelsPerMeter = 50.0f;
    int sidebarMode = 0;
};

struct EnvironmentSettings {
    float gravity = 9.8f;
    float airDensity = 1.225f;
    float height = 10.0f;
    float groundRestitution = 0.8f;
};

struct ObjectSettings {
    float mass = 1.0f;
    float radius = 0.1f;
    float restitution = 0.8f;
};

struct SceneSettings {
    SimulationSettings simulation;
    EnvironmentSettings environment;
    ObjectSettings object;

    bool isDirty = false;
};

#endif