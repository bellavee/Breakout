
#include "Paddle.h"

Paddle::Paddle(const std::string& filename, int windowWidth, int windowHeight)
    : _windowWidth(windowWidth)
    , _windowHeight(windowHeight)
    , _texture()
    , _sprite(_texture)
{
    if (!_texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }

    _position.x = (_windowWidth - GetTextureScaleSizeX()) / 2.0f;
    _position.y = _windowHeight - 100.0f;

    sf::Sprite tmp(_texture);
    _sprite = tmp;
    _sprite.setTexture(_texture);
    _sprite.setPosition(_position);
    _sprite.setScale(sf::Vector2f(GameConstants::SCALE_SIZE, GameConstants::SCALE_SIZE));
}

void Paddle::Update(GameWindow &window) {
    HandleMouseInput(window);
    _sprite.setPosition(_position);
}

void Paddle::Draw(GameWindow &window) {
    window.Draw(_sprite);
}

void Paddle::IncreaseSize(float sizeX, float sizeY)
{
    _sprite.setScale( _sprite.getScale() + sf::Vector2f{sizeX, sizeY});
}

void Paddle::DecreaseSize(float sizeX, float sizeY)
{
    _sprite.setScale(_sprite.getScale() - sf::Vector2f{sizeX, sizeY});
}

void Paddle::HandleMouseInput(GameWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window.GetGameWindow());

    if (mousePos.x >= 0 && mousePos.x <= _windowWidth) {
        float paddleHalfWidth = (_sprite.getGlobalBounds().size.x / 2.0f);
        _position.x = std::clamp((mousePos.x - paddleHalfWidth), 0.0f,_windowWidth - GetTextureScaleSizeX());
    }
}
