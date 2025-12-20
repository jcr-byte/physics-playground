#include <sstream>
#include <SFML/Graphics.hpp>
#include "../core/EventHandler.h"
#include "../entities/Mass.h"
#include <imgui.h>
#include <imgui-SFML.h>

void sceneOne() {

    // creates window and program icon
    sf::RenderWindow window(sf::VideoMode({1600, 900}), "Physics Playground");
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
    camera.setSize(sf::Vector2f(1600.0f, 900.0f));
    camera.setCenter(sf::Vector2f(1600.0f / 2.f, 900.0f / 2.f));
    window.setView(camera);

    // global sizing variables
    float sidebarWidth = 250.0f;
    float sidebarPos = static_cast<float>(window.getSize().x) - sidebarWidth;
    float tabWidth = 40.0f;
    float screenWidth = static_cast<float>(window.getSize().x);
    float screenHeight = static_cast<float>(window.getSize().y);
    float sceneWidth = screenWidth - sidebarWidth;

    // logic for setting up mass 1
    Mass mainMass(sf::Vector2f(sceneWidth / 2, screenHeight / 2), 1, 5);
    sf::Vector2f gravityForce(0.0f, mainMass.getMass() * 100);

    // creates ground
    sf::VertexArray ground(sf::PrimitiveType::Lines, 2);
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

        // setup sidebar ui
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

        // setup sidebar buttons Ui
        ImGui::SetNextWindowPos(ImVec2(sidebarPos - tabWidth, 0));
        ImGui::SetNextWindowSize(ImVec2(tabWidth, 200.0f));

        ImGuiWindowFlags tabFlags = ImGuiWindowFlags_NoDecoration | 
                                    ImGuiWindowFlags_NoMove | 
                                    ImGuiWindowFlags_NoResize | 
                                    ImGuiWindowFlags_NoSavedSettings |
                                    ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

        if (ImGui::Begin("SidebarTabs", nullptr, tabFlags)) {
            if (ImGui::Button("T", ImVec2(tabWidth, 40))) {}
            if (ImGui::Button("S", ImVec2(tabWidth, 40))) {}

            ImGui::End();
        }

        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        
        float groundY = 800.0f;

        ground[0].position = sf::Vector2f(0.f, groundY);
        ground[1].position = sf::Vector2f(sceneWidth, groundY);

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