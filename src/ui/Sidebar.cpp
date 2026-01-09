#include <imgui.h>
#include <imgui-SFML.h>
#include "Sidebar.h"
#include "../core/Settings.h"

Sidebar::Sidebar() {
    sidebarMode = 0;
    width = 270.0f;
    tabWidth = 40.0f;
    inputFieldWidth = 80.0f;
}

void Sidebar::renderTelemetryPanel() {
    ImGui::PushFont(headerOneFont);
    ImGui::Text("Telemetry");
    ImGui::PopFont();
}

void Sidebar::renderSettingsPanel(SceneSettings& settings) {
    ImGui::PushFont(headerOneFont);
    ImGui::Text("Settings");
    ImGui::PopFont();

    if (ImGui::CollapsingHeader("Environment", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::SetNextItemWidth(inputFieldWidth);
        if (ImGui::DragFloat("Gravity (m/s_2)", &settings.environment.gravity, 0.01f, 0.0f, 20.0f, "%.2f")) {
            settings.isDirty = true;
        }
        ImGui::SetNextItemWidth(inputFieldWidth);
        if (ImGui::DragFloat("Air Density (m/s_2)", &settings.environment.airDensity, 0.01f, 0.0f, 20.0f, "%.2f"))  {
            settings.isDirty = true;
        }
        ImGui::SetNextItemWidth(inputFieldWidth);
        if (ImGui::DragFloat("Height (m)", &settings.environment.height, 0.01f, 0.0f, 20.0f, "%.2f")) {
            settings.isDirty = true;
        }
        ImGui::SetNextItemWidth(inputFieldWidth);
        if (ImGui::DragFloat("Ground Restitution", &settings.environment.groundRestitution, 0.01f, 0.0f, 20.0f, "%.2f")) {
            settings.isDirty = true;
        }
    }
    if (ImGui::CollapsingHeader("Object Properties", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::SetNextItemWidth(inputFieldWidth);
        if (ImGui::DragFloat("Mass (g)", &settings.object.mass, 0.01f, 0.0f, 20.0f, "%.2f")) {
            settings.isDirty = true;
        }
        ImGui::SetNextItemWidth(inputFieldWidth);
        if (ImGui::DragFloat("Radius (m)", &settings.object.radius, 0.01f, 0.0f, 20.0f, "%.2f")) {
            settings.isDirty = true;
        }
        ImGui::SetNextItemWidth(inputFieldWidth);
        if (ImGui::DragFloat("Mass Restitution", &settings.object.restitution, 0.01f, 0.0f, 20.0f, "%.2f")) {
            settings.isDirty = true;
        }
    }
    if (ImGui::CollapsingHeader("Visualization", ImGuiTreeNodeFlags_DefaultOpen)) {
    }
}

void Sidebar::renderTabButtons(float sidebarPosX, SceneSettings& settings) {
    ImGui::SetNextWindowPos(ImVec2(sidebarPosX - tabWidth, 0));
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
            settings.simulation.sidebarMode = 0;
        }
        if (ImGui::Button("S", ImVec2(tabWidth, 40))) {
            settings.simulation.sidebarMode = 1;
        }

        ImGui::End();
    }

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

void Sidebar::loadFonts(ImGuiIO& io) {
    this->headerOneFont = io.Fonts->AddFontFromFileTTF("assets/fonts/CONSOLAB.ttf", 20.0f);
    this->headerTwoFont = io.Fonts->AddFontFromFileTTF("assets/fonts/CONSOLA.ttf", 18.0f);
}

void Sidebar::render(SceneSettings& settings) {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImVec2 sidebarPos = ImVec2(
        viewport->WorkPos.x + viewport->WorkSize.x - width,
        viewport->WorkPos.y
    );

    renderTabButtons(sidebarPos.x, settings);

    ImGui::SetNextWindowPos(sidebarPos);
    ImGui::SetNextWindowSize(ImVec2(width, viewport->WorkSize.y));

    ImGuiWindowFlags sidebarFlags = ImGuiWindowFlags_NoCollapse | 
                                    ImGuiWindowFlags_NoResize | 
                                    ImGuiWindowFlags_NoMove | 
                                    ImGuiWindowFlags_NoTitleBar |
                                    ImGuiWindowFlags_NoBringToFrontOnFocus;

    if (ImGui::Begin("Sidebar", nullptr, sidebarFlags)) {
        if (settings.simulation.sidebarMode == 0) {
            renderTelemetryPanel();
        }
        if (settings.simulation.sidebarMode == 1) {
            renderSettingsPanel(settings);
        }
    }

    ImGui::End();
}