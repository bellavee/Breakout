
#include "Ball.h"

#include "../include/Constants.h"

Ball::Ball(const std::string &filePath, int windowWidth, int windowHeight, float speed, const sf::Vector2f &startPosition, const sf::Vector2f &velocity) 
    : _windowWidth(windowWidth)
    , _windowHeight(windowHeight)
    , _speed(speed)
    , _position(startPosition)
    , _velocity(velocity)
    , _texture()
    , _sprite(_texture)
{
    
    if (!_texture.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    sf::Sprite tmp(_texture);
    _sprite = tmp;
    _sprite.setTexture(_texture);
    _sprite.setPosition(_position);
    _sprite.setScale({GameConstants::SCALE_SIZE, GameConstants::SCALE_SIZE});
}

void Ball::Update()
{
    _sprite.move(_velocity * _speed);
    CheckWallCollisions();
}

void Ball::Draw(GameWindow &window)
{
    window.Draw(_sprite);
}

void Ball::CheckWallCollisions()
{
    sf::FloatRect ballRect = _sprite.getGlobalBounds();
    sf::Vector2f pos = _sprite.getPosition();

    if (pos.x < 0) {
        pos.x = 0;
        _velocity.x = -_velocity.x;
    } else if (pos.x + ballRect.size.x >  _windowWidth) {
        pos.x = _windowWidth - ballRect.size.x; 
        _velocity.x = -_velocity.x;
    }
    
    if (pos.y < 0) {
        pos.y = 0;
        _velocity.y = -_velocity.y;
    } else if (pos.y + ballRect.size.y > _windowHeight) {
        pos.y = _windowHeight - ballRect.size.y;
        _velocity.y = -_velocity.y;
    }
    _sprite.setPosition(pos);
}

void Ball::ChangeDirection()
{
    float angle = (float)(rand() % 360);
    _velocity = { _speed * std::cos(angle), _speed * std::sin(angle) };
}