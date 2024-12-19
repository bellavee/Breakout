
#ifndef PADDLE_H
#define PADDLE_H

#include "Breakout.h"
#include "GameWindow.h"
#include "../include/Constants.h"



class Paddle {
public:
    Paddle(const std::string& filename, int windowWidth, int windowHeight);
    ~Paddle() = default;

    void Update(GameWindow &window);
    void Draw(GameWindow &window);
    int GetTextureScaleSizeX() const { return _texture.getSize().x * GameConstants::SCALE_SIZE; }
    int GetTextureScaleSizeY() const { return _texture.getSize().y * GameConstants::SCALE_SIZE; }
    sf::Sprite& GetSprite() { return _sprite; }

private:
    void HandleMouseInput(GameWindow &window);

   // sf::RenderWindow& _window;
    sf::Texture _texture;
    sf::Sprite _sprite;

    sf::Vector2f _position;
    float _windowWidth;
    float _windowHeight;

};



#endif //PADDLE_H
