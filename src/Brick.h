
#ifndef BRICK_H
#define BRICK_H
#include "SFML/System/Vector2.hpp"


class Brick {
public:
    Brick();
    ~Brick();

    void CheckCollision();

private:
    sf::Vector2f _position;
    int hitPoints;

};



#endif //BRICK_H
