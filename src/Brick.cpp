#include "Brick.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

Brick::Brick(sf::Vector2f pos) : _position(pos), _hasCrack(false), _isDestroy(false) {
}

Brick::~Brick() {
}

void Brick::LoadImage(const std::string& filename) {
    if (!_texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
}

void Brick::LoadCrackOverlay(const std::string& filename) {
    if (!_crackTexture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load crack texture: " + filename);
    }
    _hasCrack = true;
}

sf::Sprite Brick::CreateSprite() {
    sf::Sprite sprite(_texture);
    sprite.setPosition(_position);
    sprite.setScale(sf::Vector2f(GameConstants::SCALE_SIZE, GameConstants::SCALE_SIZE));
    return sprite;
}

void Brick::Draw(GameWindow& window) {
    if (!_isDestroy) {
        sf::Sprite baseSprite(_texture);
        baseSprite.setPosition(_position);
        baseSprite.setScale(sf::Vector2f(GameConstants::SCALE_SIZE, GameConstants::SCALE_SIZE));
        window.Draw(baseSprite);

        if (_hasCrack) {
            sf::Sprite crackSprite(_crackTexture);
            crackSprite.setPosition(_position);
            crackSprite.setScale(sf::Vector2f(GameConstants::SCALE_SIZE, GameConstants::SCALE_SIZE));
            window.Draw(crackSprite);
        }
    }
}

void Brick::OnCollision() {
    if (_isDestroy) return;

    _hitPoints--;

    if (_hitPoints <= 0) {
        _isDestroy = true;
        SetState(Destroy);
        return;
    }

    std::string crackFilename;
    if (_hitPoints == 3) {
        crackFilename = "../assets/crack-1.png";
        SetState(Level3);
    }
    else if (_hitPoints == 2) {
        crackFilename = "../assets/crack-2.png";
        SetState(Level2);
    }
    else if (_hitPoints == 1) {
        crackFilename = "../assets/crack-3.png";
        SetState(Level1);
    }

    if (!crackFilename.empty()) {
        LoadCrackOverlay(crackFilename);
    }
}

void Brick::OnStateChange() {
    if (_state == Destroy) {
        _isDestroy = true;
    }
}

void Brick::SetState(BrickState state) {
    _state = state;
    _hitPoints = static_cast<int>(state);
    OnStateChange();
}

void Brick::Update() {
}

void Brick::CheckCollision() {
}