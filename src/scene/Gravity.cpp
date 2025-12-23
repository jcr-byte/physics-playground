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
    io.Fonts->AddFontDefault();
    ImFont* headerOneFont = io.Fonts->AddFontFromFileTTF("assets/fonts/CONSOLAB.ttf", 20.0f);
    ImFont* headerTwoFont = io.Fonts->AddFontFromFileTTF("assets/fonts/CONSOLA.ttf", 18.0f);
    ImGui::SFML::UpdateFontTexture();

    // inits camera
    sf::View camera;
    camera.setSize(sf::Vector2f(1600.0f, 900.0f));
    camera.setCenter(sf::Vector2f(1600.0f / 2.f, 900.0f / 2.f));
    window.setView(camera);

    // global sizing variables
    float toolbarWidth = 100.0f;
    float toolbarHeight = 50.0f;
    float toolbarButtonsPos = 0.0f;
    float sidebarWidth = 250.0f;
    float sidebarPos = static_cast<float>(window.getSize().x) - sidebarWidth;
    float tabWidth = 40.0f;
    float screenWidth = static_cast<float>(window.getSize().x);
    float screenHeight = static_cast<float>(window.getSize().y);
    float sceneWidth = screenWidth - sidebarWidth;
    float groundY = 800.0f;

    // global initial variables
    static float gravity = 9.8f;
    static float airResistance = 1.0f;
    static float height = 10.0f;
    static float groundRestitution = 0.1f;
    static float mass = 1.0f;
    static float radius = 5.0f;
    static float massRestitution = 0.4f;
    float pixelsPerMeter = 50.0f;
    float pixelHeight = groundY - (height * pixelsPerMeter);
    

    // logic for setting up mass 1
    Mass mainMass(sf::Vector2f(sceneWidth / 2,pixelHeight), 1, 5);
    sf::Vector2f gravityForce(0.0f, mainMass.getMass() * 100);

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
                mainMass.setHeight(pixelHeight);
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
                    ImGui::SetNextItemWidth(80.0f);
                    ImGui::DragFloat("Gravity (m/s_2)", &gravity, 0.01f, 0.0f, 20.0f, "%.2f");
                    ImGui::DragFloat("Air Resistance (m/s_2)", &airResistance, 0.01f, 0.0f, 20.0f, "%.2f");
                    if (ImGui::DragFloat("Height (m)", &height, 0.01f, 0.0f, 20.0f, "%.2f")) {
                        pixelHeight = groundY - (height * pixelsPerMeter);
                        mainMass.setHeight(pixelHeight);
                    }
                    ImGui::DragFloat("Ground Restitution", &groundRestitution, 0.01f, 0.0f, 20.0f, "%.2f");
                }
                if (ImGui::CollapsingHeader("Object Properties")) {
                    ImGui::SetNextItemWidth(80.0f);
                    ImGui::DragFloat("Mass (g)", &mass, 0.01f, 0.0f, 20.0f, "%.2f");
                    ImGui::DragFloat("Radius (m)", &radius, 0.01f, 0.0f, 20.0f, "%.2f");
                    ImGui::DragFloat("Mass Restitution", &massRestitution, 0.01f, 0.0f, 20.0f, "%.2f");
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

        ground[0].position = sf::Vector2f(0.f, groundY);
        ground[1].position = sf::Vector2f(sceneWidth, groundY);

        window.clear();
        window.draw(ground);

        mainMass.draw(window);

        if (!isPaused) {
            mainMass.applyForce(gravityForce);
            mainMass.update(frameTime);
            mainMass.handleGroundCollision(ground[0].position.y, 0.8);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}