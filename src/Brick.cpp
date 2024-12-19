
#include "Brick.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

Brick::Brick(sf::Vector2f pos) : _position(pos) {
}

Brick::~Brick() {

}

void Brick::LoadImage(const std::string& filename) {
    if (!_texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
}

sf::Sprite Brick::CreateSprite() {
    sf::Sprite sprite(_texture);
    sprite.setPosition(_position);
    sprite.setScale(sf::Vector2f(GameConstants::SCALE_SIZE, GameConstants::SCALE_SIZE));
    return sprite;
}

void Brick::Draw() {
}

void Brick::Update() {
}

void Brick::CheckCollision() {
}

void Brick::OnCollision() {
    if (_isDestroy) return;

    _hitPoints--;

    if (_hitPoints <= 0) {
        _isDestroy = true;
        SetState(Destroy);
        return;
    }

    if (_hitPoints == 3) SetState(Level3);
    else if (_hitPoints == 2) SetState(Level2);
    else if (_hitPoints == 1) SetState(Level1);
}

void Brick::OnStateChange() {
    std::string filename;
    switch (_state) {
        case Level4:
            filename = "../assets/crack-1.png";
        break;
        case Level3:
            filename = "../assets/crack-2.png";
        break;
        case Level2:
            filename = "../assets/crack-3.png";
        break;
        case Level1:
            filename = "../assets/crack-4.png";
        break;
        case Destroy:
            _isDestroy = true;
        return;
    }
    LoadImage(filename);
}

void Brick::SetState(BrickState state) {
    _state = state;
    _hitPoints = static_cast<int>(state);
    OnStateChange();
}
