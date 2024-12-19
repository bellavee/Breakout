
#ifndef BALL_H
#define BALL_H

#include "Breakout.h"
#include "GameWindow.h"

class Ball {
public:
    Ball(const std::string &filePath, int windowWidth, int windowHeight, float speed, const sf::Vector2f &startPosition, const sf::Vector2f &velocity);
    void Update();
    void Draw(GameWindow &window);
    void CheckWallCollisions();
    void ChangeDirection();
private:
    sf::Vector2f _velocity;
    sf::Vector2f _position;
    float _speed;
    sf::Texture _texture;
    sf::Sprite _sprite;
    int _windowWidth;
    int _windowHeight;
};



#endif //BALL_H
