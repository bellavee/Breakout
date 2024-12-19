
#include "Paddle.h"

Paddle::Paddle(int windowWidth, int windowHeight) 
    : _windowWidth(windowWidth)
    , _windowHeight(windowHeight)
{
}

void Paddle::LoadImage(const std::string& filename) {
    bool success = _texture.loadFromFile(filename);
    if (!success) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }

    _position.x = (_windowWidth - GetTextureScaleSizeX()) / 2.0f;
    _position.y = _windowHeight - 100.0f;

    //_window.getSize().x
    // _window.getSize().y
}

sf::Sprite Paddle::CreateSprite() {
    sf::Sprite sprite(_texture);
    sprite.setPosition(_position);
    sprite.setScale(sf::Vector2f(GameConstants::SCALE_SIZE, GameConstants::SCALE_SIZE));
    return sprite;
}

void Paddle::Update(GameWindow &window) {
    HandleMouseInput(window);
}

void Paddle::Draw(GameWindow &window) {
    window.Draw(CreateSprite());
}

void Paddle::HandleMouseInput(GameWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window.GetGameWindow());

    if (mousePos.x >= 0 && mousePos.x <= _windowWidth) {
        float paddleHalfWidth = (CreateSprite().getGlobalBounds().size.x / 2.0f);
        _position.x = std::clamp((mousePos.x - paddleHalfWidth), 0.0f,_windowWidth - GetTextureScaleSizeX());
    }
}
