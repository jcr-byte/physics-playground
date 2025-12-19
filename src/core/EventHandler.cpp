#include "EventHandler.h"
#include <imgui-SFML.h>

bool EventHandler::processEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(window, *event);

        if (event->is<sf::Event::Closed>()) {
            return true;
        }

        if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            sf::View view = window.getView();
            sf::Vector2f viewSize = view.getSize();

            float windowRatio = static_cast<float>(resized->size.x) / resized->size.y;
            float viewRatio = viewSize.x / viewSize.y;

            if (windowRatio > viewRatio) {
                view.setSize(sf::Vector2f(viewSize.y * windowRatio, viewSize.y));
            } else {
                view.setSize(sf::Vector2f(viewSize.x, viewSize.x / windowRatio));
            }
            window.setView(view);
        }
    }
    return false;
}