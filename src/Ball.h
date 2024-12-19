
#ifndef BALL_H
#define BALL_H

#include "Breakout.h"
#include "Brick.h"
#include "GameWindow.h"
#include "Paddle.h"

class Ball {
public:
    Ball(const std::string &filePath, int windowWidth, int windowHeight, float speed, const sf::Vector2f &startPosition, const sf::Vector2f &velocity);
    void Update();
    void Draw(GameWindow &window);
    void CheckCollisions(Paddle& paddle, std::vector<std::shared_ptr<Brick>>& bricks);
    void ChangeDirection();

    sf::FloatRect GetBounds() const { return _ballOutline.getGlobalBounds(); }
    float GetRadius() { return _radius; };
    void IncreaseRadius(float radius);
    void IncreaseSpeed(float speed) { _speed += speed; }
private:
    void CheckWallCollisions();
    void CheckPaddleCollision(Paddle& paddle);
    void CheckBrickCollision(std::vector<std::shared_ptr<Brick>>& bricks);

    sf::Vector2f _velocity;
    sf::Vector2f _position;
    float _speed;
    float _radius;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::CircleShape _ballOutline;
    int _windowWidth;
    int _windowHeight;
};



#endif //BALL_H
