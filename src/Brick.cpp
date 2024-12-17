
#include "Brick.h"

#include "SFML/Graphics/Sprite.hpp"

Brick::Brick(sf::Vector2f pos)
    : _position(pos)
{
}

Brick::~Brick() {

}

sf::Sprite Brick::CreateSprite() {
    _texture.loadFromFile("../assets/brick-pink.png");
    sf::Sprite sprite(_texture);
    sprite.setPosition(_position);
    sprite.setScale(sf::Vector2f(3, 3));
    return sprite;
}

void Brick::Draw() {

}

void Brick::Update() {
}

void Brick::CheckCollision() {
}

void Brick::OnCollision(sf::Vector2f dir) {
}

void Brick::OnStateChange() {
}
