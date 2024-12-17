
#ifndef PADDLE_H
#define PADDLE_H
#include "SFML/System/Vector2.hpp"


class Paddle {
public:
    Paddle();
    ~Paddle();

private:
    float _speed;
    sf::Vector2f _position;

};



#endif //PADDLE_H
