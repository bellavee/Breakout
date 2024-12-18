#include <SFML/Graphics.hpp>

#include "Brick.h"
#include "GameMap.h"

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "My window");

    GameMap* map = new GameMap(window);
    map->LoadMap("../levels/1.txt");

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::White);


        map->Draw();

        // end the current frame
        window.display();
    }
}
