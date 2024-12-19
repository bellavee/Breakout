
#ifndef PADDLE_H
#define PADDLE_H

#include "Breakout.h"
#include "GameWindow.h"
#include "../include/Constants.h"



class Paddle {
public:
    Paddle(int windowWidth, int windowHeight);
    ~Paddle() = default;

    void LoadImage(const std::string& filename);
    void Update(GameWindow &window);
    void Draw(GameWindow &window);
    sf::Sprite CreateSprite();
    int GetTextureScaleSizeX() const { return _texture.getSize().x * GameConstants::SCALE_SIZE; }
    int GetTextureScaleSizeY() const { return _texture.getSize().y * GameConstants::SCALE_SIZE; }

private:
    void HandleMouseInput(GameWindow &window);

   // sf::RenderWindow& _window;
    sf::Texture _texture;

    sf::Vector2f _position;
    float _windowWidth;
    float _windowHeight;

};



#endif //PADDLE_H
