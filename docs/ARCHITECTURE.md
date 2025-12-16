# Architecture Documentation

This document captures the class designs and architectural decisions for the Physics Playground project.

---

## Class Diagrams

### Mass

The `Mass` class represents a physical body in the simulation. It uses **composition** to separate physics state from visual representation.

```
┌─────────────────────────────────────────────────────┐
│                       Mass                          │
├─────────────────────────────────────────────────────┤
│  - position : sf::Vector2f                          │
│  - velocity : sf::Vector2f                          │
│  - acceleration : sf::Vector2f                      │
│  - mass : float                                     │
│  - shape : sf::CircleShape                          │
├─────────────────────────────────────────────────────┤
│  + Mass(position: sf::Vector2f, mass: float,        │
│         radius: float)                              │
├─────────────────────────────────────────────────────┤
│  + applyForce(force: sf::Vector2f) : void           │
│  + update(dt: float) : void                         │
│  + draw(window: sf::RenderWindow&) : void           │
├─────────────────────────────────────────────────────┤
│  + getPosition() : sf::Vector2f                     │
│  + setPosition(pos: sf::Vector2f) : void            │
│  + getVelocity() : sf::Vector2f                     │
│  + setVelocity(vel: sf::Vector2f) : void            │
│  + getMass() : float                                │
│  + getShape() : sf::CircleShape&                    │
└─────────────────────────────────────────────────────┘
```

**Location:** `src/entities/Mass.h`, `src/entities/Mass.cpp`

---

### EventHandler

The `EventHandler` class encapsulates SFML event polling, separating input handling from the main game loop.

```
┌─────────────────────────────────────────────────────┐
│                   EventHandler                      │
├─────────────────────────────────────────────────────┤
│  (no members)                                       │
├─────────────────────────────────────────────────────┤
│  + processEvents(window: sf::RenderWindow&) : bool  │
└─────────────────────────────────────────────────────┘
```

**Location:** `src/core/EventHandler.h`, `src/core/EventHandler.cpp`

---

## Project Structure

```
src/
├── core/               # Engine infrastructure
│   ├── EventHandler.h
│   └── EventHandler.cpp
├── entities/           # Physics objects
│   ├── Mass.h
│   └── Mass.cpp
└── main.cpp            # Entry point and game loop
```

---

