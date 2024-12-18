
#include "Brick.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

Brick::Brick(sf::Vector2f pos) : _position(pos) {
}

Brick::~Brick() {

}

void Brick::LoadImage(const std::string& filename) {
    bool success = _texture.loadFromFile(filename);
    if (!success) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
}

sf::Sprite Brick::CreateSprite() {
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

void Brick::SetState(BrickState state) {
    _state = state;
    _hitPoints = static_cast<int>(state);
    OnStateChange();
}
