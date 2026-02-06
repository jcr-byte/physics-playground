#include "Application.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include "../core/EventHandler.h"
#include "../core/Settings.h"
#include "../ui/Sidebar.h"
#include "Gravity.h"
#include <imgui.h>
#include <imgui-SFML.h>


void createApplication(){
    // creates window and program icon
    sf::RenderWindow window(sf::VideoMode({1600, 900}), "Physics Playground");
    sf::Image icon;
    if (icon.loadFromFile("assets/icons/icon.png")) {
        window.setIcon(icon.getSize(), icon.getPixelsPtr());
    }

    // instantiates event handler
    EventHandler eventHandler;

    // inits sidebar UI
    Sidebar sidebarl;

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
}
