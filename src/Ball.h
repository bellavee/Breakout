
#ifndef BALL_H
#define BALL_H
#include "SFML/System/Vector2.hpp"


class Ball {
public:
    Ball();
    ~Ball();

    void UpdateCollision();
    void CheckCollision();

private:
    sf::Vector2f _velocity;
    sf::Vector2f _position;
    float _speed;

};



#endif //BALL_H
