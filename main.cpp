#include <SFML/Graphics.hpp>
#include "Entity.hpp"

int main(int argc, char** argv){
    sf::RenderWindow window(sf::VideoMode(200,600), "SFML Works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}
