#include <SFML/Graphics.hpp>

#include "Brick.h"
#include "GameMap.h"
#include "Paddle.h"

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "My window");

    window.setFramerateLimit(120);
    window.setMouseCursorVisible(false);

    std::unique_ptr<GameMap> map = std::make_unique<GameMap>(window);
    map->LoadMap("../levels/1.txt");

    std::unique_ptr<Paddle> paddle = std::make_unique<Paddle>(window);
    paddle->LoadImage("../assets/paddle.png");


    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        paddle->Update();

        // clear the window with black color
        window.clear(sf::Color::White);
        map->Draw();
        paddle->Draw();


        // end the current frame
        window.display();
    }

    return 0;
}
