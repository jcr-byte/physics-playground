#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Window");

    const sf::Font font("/System/Library/Fonts/Helvetica.ttc");
    sf::Text text(font, "Hello SFML", 50);
    
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.draw(text);

        window.display();
    }
}