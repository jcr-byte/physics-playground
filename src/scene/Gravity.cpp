#include <sstream>
#include <SFML/Graphics.hpp>
#include "../core/EventHandler.h"
#include "../entities/Mass.h"
#include <imgui.h>
#include <imgui-SFML.h>

void sceneOne() {

    // creates window and program icon
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Physics Playground");
    sf::Image icon;
    if (icon.loadFromFile("assets/icons/icon.png")) {
        window.setIcon(icon.getSize(), icon.getPixelsPtr());
    }

    // instantiates event handler
    EventHandler eventHandler;

    // inits ImGui
    if (!ImGui::SFML::Init(window)) {
        return;
    }

    // inits camera
    sf::View camera;
    camera.setSize(sf::Vector2f(800.f, 600.f));
    camera.setCenter(sf::Vector2f(400.f, 300.f));
    window.setView(camera);

    // logic for setting up mass 1
    Mass mainMass(sf::Vector2f(400, 100), 1, 5);
    sf::Vector2f gravityForce(0.0f, mainMass.getMass() * 100);

    // creates ground
    sf::VertexArray ground(sf::PrimitiveType::Lines, 2);
    ground[0].position = sf::Vector2f(0.f, 500.f);
    ground[1].position = sf::Vector2f(800.f, 500.f);
    ground[0].color = sf::Color::White;
    ground[1].color = sf::Color::White;

    // logic for calculating fps
    sf::Clock frameClock;
    float frameTime = 0.0f;



    while (window.isOpen()) {
        if (eventHandler.processEvents(window)){
            window.close();
        }

        sf::Time dt = frameClock.restart();
        frameTime = dt.asSeconds();
        ImGui::SFML::Update(window, dt);

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        float sidebarWidth = 150.0f;

        ImVec2 windowPos = ImVec2(
            viewport->WorkPos.x + viewport->WorkSize.x - sidebarWidth,
            viewport->WorkPos.y
        );

        ImGui::SetNextWindowPos(windowPos);
        ImGui::SetNextWindowSize(ImVec2(sidebarWidth, viewport->WorkSize.y));

        ImGuiWindowFlags sidebarFlags = ImGuiWindowFlags_NoCollapse | 
                                        ImGuiWindowFlags_NoResize | 
                                        ImGuiWindowFlags_NoMove | 
                                        ImGuiWindowFlags_NoTitleBar |
                                        ImGuiWindowFlags_NoBringToFrontOnFocus;

        if (ImGui::Begin("Telemetry", nullptr, sidebarFlags)) {
            ImGui::Text("Kinematics");
        }

        ImGui::End();

        window.clear();
        window.draw(ground);
        mainMass.draw(window);
        mainMass.applyForce(gravityForce);
        mainMass.update(frameTime);
        mainMass.handleGroundCollision(ground[0].position.y, 0.8);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}