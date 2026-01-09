#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <imgui.h>
#include <imgui-SFML.h>

struct SceneSettings;

class Sidebar {
private:
    int sidebarMode;
    float width;
    float tabWidth;
    float inputFieldWidth;
    ImFont* headerOneFont;
    ImFont* headerTwoFont;

    void renderTelemetryPanel();
    void renderSettingsPanel(SceneSettings& settings);
    void renderTabButtons(float sidebarPosX, SceneSettings& settings);
public:
    Sidebar();
    void loadFonts(ImGuiIO& io);
    void render(SceneSettings& settings);

};

#endif