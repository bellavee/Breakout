
#include "Paddle.h"

Paddle::Paddle(sf::RenderWindow& window) : _window(window), _windowWidth(window.getSize().x) {
}

void Paddle::LoadImage(const std::string& filename) {
    bool success = _texture.loadFromFile(filename);
    if (!success) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }

    _position.x = (_window.getSize().x - GetTextureScaleSizeX()) / 2.0f;
    _position.y = _window.getSize().y - 100.0f;
}

sf::Sprite Paddle::CreateSprite() {
    sf::Sprite sprite(_texture);
    sprite.setPosition(_position);
    sprite.setScale(sf::Vector2f(GameConstants::SCALE_SIZE, GameConstants::SCALE_SIZE));
    return sprite;
}

void Paddle::Update() {
    HandleMouseInput();
}

void Paddle::Draw() {
    _window.draw(CreateSprite());
}

void Paddle::HandleMouseInput() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

    if (mousePos.x >= 0 && mousePos.x <= _windowWidth) {
        float paddleHalfWidth = (CreateSprite().getGlobalBounds().size.x / 2.0f);
        _position.x = std::clamp((mousePos.x - paddleHalfWidth), 0.0f,_windowWidth - GetTextureScaleSizeX());
    }
}
