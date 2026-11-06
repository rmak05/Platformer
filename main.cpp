#include <SFML/Graphics.hpp>
#include <optional>

int main(){
    sf::RenderWindow window(
        sf::VideoMode({800u, 600u}),
        "SFML-CMake-VSCode Test"
    );

    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition({300.f, 200.f});

    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()) window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
}
