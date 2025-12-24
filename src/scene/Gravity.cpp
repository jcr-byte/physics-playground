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

    // load font
    ImGuiIO& io = ImGui::GetIO();
    ImFont* mainFont = io.Fonts->AddFontFromFileTTF("assets/fonts/CONSOLA.ttf", 12.0f);
    io.FontDefault = mainFont;
    ImFont* headerOneFont = io.Fonts->AddFontFromFileTTF("assets/fonts/CONSOLAB.ttf", 20.0f);
    ImFont* headerTwoFont = io.Fonts->AddFontFromFileTTF("assets/fonts/CONSOLA.ttf", 18.0f);
    ImGui::SFML::UpdateFontTexture();

    // inits camera
    sf::View camera;
    camera.setSize(sf::Vector2f(1600.0f, 900.0f));
    camera.setCenter(sf::Vector2f(1600.0f / 2.f, 900.0f / 2.f));
    window.setView(camera);

    // global sizing variables

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
    float pixelsPerMeter = 50.0f;
    float groundYPixels = 800.0f;
    float groundYMeters = groundYPixels / pixelsPerMeter;

    // global initial variables
    static float gravity = 9.8f;
    static float airDensity = 1.225f;
    static float height = 10.0f;
    static float groundRestitution = 0.8f;
    static float massSize = 1.0f;
    static float radius = 0.1f;
    static float massRestitution = 0.8f;
    float totalRestitution = massRestitution * groundRestitution;
    
    // logic for setting up massSize 1
    Mass mainMass(sf::Vector2f((sceneWidth / 2) / pixelsPerMeter, groundYMeters - height), massSize, radius);
    sf::Vector2f gravityForce = sf::Vector2f(0.0f, massSize * gravity);

    // creates ground
    sf::VertexArray ground(sf::PrimitiveType::Lines, 2);
    ground[0].color = sf::Color::White;
    ground[1].color = sf::Color::White;

    // logic for calculating fps
    sf::Clock frameClock;
    float frameTime = 0.0f;

    // toolbar variables
    bool isPaused = true;

    // sidebar variables
    int sidebarMode = 0;

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
                if (isPaused) {
                    isPaused = false;
                } else {
                    isPaused = true;
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Reset", ImVec2(tabWidth, 40))) {
                groundYMeters = groundYPixels / pixelsPerMeter;
                mainMass.setHeight(groundYMeters - height);
                mainMass.setVelocity(sf::Vector2f(0, 0));
            }

            ImGui::End();
        }

        ImGui::PopStyleColor();
        ImGui::PopStyleVar(3);
        

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

        if (ImGui::Begin("Sidebar", nullptr, sidebarFlags)) {
            if (sidebarMode == 0) {
                ImGui::PushFont(headerOneFont);
                ImGui::Text("Telemetry");
                ImGui::PopFont();
            }
            if (sidebarMode == 1) {

                ImGui::PushFont(headerOneFont);
                ImGui::Text("Settings");
                ImGui::PopFont();

                if (ImGui::CollapsingHeader("Environment")) {
                    ImGui::SetNextItemWidth(sidebarInputFieldWidth);
                    if (ImGui::DragFloat("Gravity (m/s_2)", &gravity, 0.01f, 0.0f, 20.0f, "%.2f")) {
                        gravityForce.y = gravity * mainMass.getMass();
                    }
                    ImGui::SetNextItemWidth(sidebarInputFieldWidth);
                    ImGui::DragFloat("Air Density (m/s_2)", &airDensity, 0.01f, 0.0f, 20.0f, "%.2f");
                    ImGui::SetNextItemWidth(sidebarInputFieldWidth);
                    if (ImGui::DragFloat("Height (m)", &height, 0.01f, 0.0f, 20.0f, "%.2f")) {
                        groundYMeters = groundYPixels / pixelsPerMeter;
                        mainMass.setHeight(groundYMeters - height);
                    }
                    ImGui::SetNextItemWidth(sidebarInputFieldWidth);
                    if (ImGui::DragFloat("Ground Restitution", &groundRestitution, 0.01f, 0.0f, 20.0f, "%.2f")) {
                        totalRestitution = massRestitution * groundRestitution;
                    }
                }
                if (ImGui::CollapsingHeader("Object Properties")) {
                    ImGui::SetNextItemWidth(sidebarInputFieldWidth);
                    if (ImGui::DragFloat("Mass (g)", &massSize, 0.01f, 0.0f, 20.0f, "%.2f")) {
                        mainMass.setMass(massSize);
                        gravityForce.y = gravity * massSize;
                    }
                    ImGui::SetNextItemWidth(sidebarInputFieldWidth);
                    if (ImGui::DragFloat("Radius (m)", &radius, 0.01f, 0.0f, 20.0f, "%.2f")) {
                        mainMass.setRadius(radius);
                    }
                    ImGui::SetNextItemWidth(sidebarInputFieldWidth);
                    if (ImGui::DragFloat("Mass Restitution", &massRestitution, 0.01f, 0.0f, 20.0f, "%.2f")) {
                        totalRestitution = massRestitution * groundRestitution;
                    }
                }
                if (ImGui::CollapsingHeader("Visualization")) {
                }
            }
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
            if (ImGui::Button("T", ImVec2(tabWidth, 40))) {
                sidebarMode = 0;
            }
            if (ImGui::Button("S", ImVec2(tabWidth, 40))) {
                sidebarMode = 1;
            }

            ImGui::End();
        }

        ImGui::PopStyleColor();
        ImGui::PopStyleVar();

        ground[0].position = sf::Vector2f(0.f, groundYPixels);
        ground[1].position = sf::Vector2f(sceneWidth, groundYPixels);

        window.clear();
        window.draw(ground);

        mainMass.draw(window);

        if (!isPaused) {
            mainMass.applyForce(gravityForce);
            mainMass.applyForce(mainMass.calculateDragForce(airDensity));
            mainMass.update(frameTime);
            mainMass.handleGroundCollision(ground[0].position.y / 50.0f, totalRestitution);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}