#include <sstream>
#include <SFML/Graphics.hpp>
#include "../core/EventHandler.h"
#include "../core/Settings.h"
#include "../entities/Mass.h"
#include "../ui/Sidebar.h"
#include "Gravity.h"
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

    // inits sidebar UI
    Sidebar sidebar;

    // inits ImGui
    if (!ImGui::SFML::Init(window)) {
        return;
    }

    // load font
    ImGuiIO& io = ImGui::GetIO();
    ImFont* mainFont = io.Fonts->AddFontFromFileTTF("assets/fonts/CONSOLA.ttf", 12.0f);
    io.FontDefault = mainFont;
    sidebar.loadFonts(io);
    ImGui::SFML::UpdateFontTexture();

    // inits camera
    sf::View camera;
    camera.setSize(sf::Vector2f(1600.0f, 900.0f));
    camera.setCenter(sf::Vector2f(1600.0f / 2.f, 900.0f / 2.f));
    window.setView(camera);

    // init all settings
    SceneSettings settings;

    // ui component positioning and sizing
    float toolbarWidth = 100.0f;
    float toolbarHeight = 50.0f;
    float sidebarWidth = 270.0f;
    float sidebarPos = static_cast<float>(window.getSize().x) - sidebarWidth;
    float sidebarInputFieldWidth = 80.0f;
    float tabWidth = 40.0f;
    float screenWidth = static_cast<float>(window.getSize().x);
    float screenHeight = static_cast<float>(window.getSize().y);
    float sceneWidth = screenWidth - sidebarWidth;
    float groundYPixels = 800.0f;
    float groundYMeters = groundYPixels / settings.simulation.pixelsPerMeter;

    // logic for setting up massSize 1
    Mass mainMass(sf::Vector2f((sceneWidth / 2) / settings.simulation.pixelsPerMeter, groundYMeters - settings.environment.height), settings.object.mass, settings.object.radius, settings.object.restitution);
    sf::Vector2f gravityForce = sf::Vector2f(0.0f, settings.object.mass * settings.environment.gravity);

    // calculates total restitution
    float totalRestitution = settings.object.restitution * settings.environment.groundRestitution;

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
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(toolbarWidth, toolbarHeight));

        ImGuiWindowFlags toolbarFlags = ImGuiWindowFlags_NoDecoration | 
                                        ImGuiWindowFlags_NoMove | 
                                        ImGuiWindowFlags_NoResize | 
                                        ImGuiWindowFlags_NoSavedSettings |
                                        ImGuiWindowFlags_AlwaysAutoResize;
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

        if (ImGui::Begin("Toolbar", nullptr, toolbarFlags)) {
            if (ImGui::Button("Play", ImVec2(tabWidth, 40))) {
                if (settings.simulation.isPaused) {
                    settings.simulation.isPaused = false;
                } else {
                    settings.simulation.isPaused = true;
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Reset", ImVec2(tabWidth, 40))) {
                groundYMeters = groundYPixels / settings.simulation.pixelsPerMeter;
                mainMass.setHeight(groundYMeters - settings.environment.height);
                mainMass.setVelocity(sf::Vector2f(0, 0));
            }

            ImGui::End();
        }

        ImGui::PopStyleColor();
        ImGui::PopStyleVar(3);

        // setup sidebar
        sidebar.render(settings);

        // update variables
        if (settings.isDirty) {
            gravityForce.y = settings.environment.gravity * settings.object.mass;
            groundYMeters = groundYPixels / settings.simulation.pixelsPerMeter;
            mainMass.setHeight(groundYMeters - settings.environment.height);
            mainMass.setMass(settings.object.mass);
            mainMass.setRadius(settings.object.radius);
            totalRestitution = settings.object.restitution * settings.environment.groundRestitution;

            settings.isDirty = false;
        }

        ground[0].position = sf::Vector2f(0.f, groundYPixels);
        ground[1].position = sf::Vector2f(sceneWidth, groundYPixels);

        window.clear();
        window.draw(ground);

        mainMass.draw(window);

        if (!settings.simulation.isPaused) {
            mainMass.applyForce(gravityForce);
            mainMass.applyForce(mainMass.calculateDragForce(settings.environment.airDensity));
            mainMass.update(frameTime);
            mainMass.handleGroundCollision(ground[0].position.y / 50.0f, totalRestitution);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}