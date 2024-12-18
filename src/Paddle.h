
#ifndef PADDLE_H
#define PADDLE_H
#include <string>

#include "../include/Constants.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"


class Paddle {
public:
    Paddle(sf::RenderWindow& window);
    ~Paddle() = default;

    void LoadImage(const std::string& filename);
    void Update();
    void Draw();
    sf::Sprite CreateSprite();
    int GetTextureScaleSizeX() const { return _texture.getSize().x * GameConstants::SCALE_SIZE; }
    int GetTextureScaleSizeY() const { return _texture.getSize().y * GameConstants::SCALE_SIZE; }

private:
    void HandleMouseInput();

    sf::RenderWindow& _window;
    sf::Texture _texture;

    sf::Vector2f _position;
    float _windowWidth;

};



#endif //PADDLE_H
