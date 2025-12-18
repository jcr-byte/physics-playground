#include <sstream>
#include <SFML/Graphics.hpp>
#include "../core/EventHandler.h"
#include "../entities/Mass.h"

void sceneOne() {

    sf::VertexArray ground(sf::PrimitiveType::Lines, 2);
    ground[0].position = sf::Vector2f(0.f, 500.f);
    ground[1].position = sf::Vector2f(800.f, 500.f);
    ground[0].color = sf::Color::White;
    ground[1].color = sf::Color::White;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Window");

    EventHandler eventHandler;

    // logic for setting up mass 1
    Mass mainMass(sf::Vector2f(400, 100), 1, 5);
    sf::Vector2f gravityForce(0.0f, mainMass.getMass() * 100);

    // // logic for fps text display
    // sf::Font font;
    // if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
    //     throw std::runtime_error("Failed to load font");
    // }
    // sf::Text fpsText(font, "FPS: --");
    // fpsText.setFont(font);
    // fpsText.setCharacterSize(24);
    // fpsText.setFillColor(sf::Color::White);
    // fpsText.setPosition(sf::Vector2f(10, 10));

    // logic for calculating fps
    sf::Clock frameClock;
    float frameTime = 0.0f;
    float fps = 0.0f;
    float fpsUpdateTimer = 0.0f;
    const float FPS_UPDATE_TIME = 0.1f;

    while (window.isOpen()) {
        if (eventHandler.processEvents(window)){
            window.close();
        }

        // // logic for displaying fps
        frameTime = frameClock.restart().asSeconds();
        fps = 1.0f / frameTime;
        fpsUpdateTimer += frameTime;

        if (fpsUpdateTimer >= FPS_UPDATE_TIME) {
            std::stringstream ss;
            ss << "FPS: " << std::fixed << std::setprecision(1) << fps;
            // fpsText.setString(ss.str());
            fpsUpdateTimer = 0.0f;
        }
        window.clear();

        window.draw(ground);

        mainMass.draw(window);
        mainMass.applyForce(gravityForce);
        mainMass.update(frameTime);
        mainMass.handleGroundCollision(ground[0].position.y, 0.8);

        window.display();
    }

}