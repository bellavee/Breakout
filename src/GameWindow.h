#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "Breakout.h"

class GameWindow {
public:
    GameWindow(int width, int height, const std::string &title);
    ~GameWindow();
    void Display();
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void Close();
    void Clear(sf::Color color);
    template<class T>
    void Draw(T gameObject) {
        _window.draw(gameObject);
    }
    sf::RenderWindow &GetGameWindow();
    std::optional<sf::Event> PollEvent();

private:
    int _width;
    int _height;
    sf::RenderWindow _window;
};

#endif //WINDOW_H
