
#ifndef PADDLE_H
#define PADDLE_H
#include <string>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"


class Paddle {
public:
    Paddle(sf::RenderWindow& window);
    ~Paddle();

    void LoadImage(const std::string& filename);
    void Update();
    void Draw();
    void HandleKeyboardInput();
    void HandleMouseInput();

private:
    sf::RenderWindow& _window;
    sf::Texture _texture;

    float _speed;
    sf::Vector2f _position;

    float _windowWidth;
    const float PADDLE_SPEED = 800.0f;

};



#endif //PADDLE_H
