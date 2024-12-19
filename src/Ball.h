
#ifndef BALL_H
#define BALL_H

#include "Breakout.h"
#include "Brick.h"
#include "GameWindow.h"
#include "Paddle.h"

class Ball {
public:
    Ball(const std::string &filePath, int windowWidth, int windowHeight, float speed, const sf::Vector2f &startPosition, const sf::Vector2f &velocity);
    void Update(Paddle& paddle);
    void Draw(GameWindow &window);
    void CheckCollisions(Paddle& paddle, std::vector<std::shared_ptr<Brick>>& bricks);
    void ChangeDirection();

    sf::FloatRect GetBounds() const { return _ballOutline.getGlobalBounds(); }
    float GetRadius() { return _radius; };
    void IncreaseRadius(float radius);
    void IncreaseSpeed(float speed) { _speed += speed; }
    void SetRadius(float radius) { _radius = radius; }
    bool IsMoving() const { return _isMoving; }

private:
    void CheckWallCollisions(Paddle& paddle);
    void CheckPaddleCollision(Paddle& paddle);
    void CheckBrickCollision(std::vector<std::shared_ptr<Brick>>& bricks);

    sf::Vector2f _velocity;
    sf::Vector2f _initialVelocity;
    sf::Vector2f _position;
    sf::Vector2f _initialPosition;

    float _speed;
    float _radius;

    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::CircleShape _ballOutline;
    int _windowWidth;
    int _windowHeight;
    bool _isMoving;
};



#endif //BALL_H
