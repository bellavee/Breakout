
#include "Ball.h"

#include "../include/Constants.h"

Ball::Ball(const std::string &filePath, int windowWidth, int windowHeight, float speed, const sf::Vector2f &startPosition, const sf::Vector2f &velocity) 
    : _windowWidth(windowWidth)
    , _windowHeight(windowHeight)
    , _speed(speed)
    , _position(startPosition)
    , _initialPosition(startPosition)
    , _velocity(velocity)
    , _initialVelocity(velocity)
    , _texture()
    , _sprite(_texture)
    , _ballOutline()
    , _isMoving(false)
{
    
    if (!_texture.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    sf::Sprite tmp(_texture);
    _sprite = tmp;
    _sprite.setTexture(_texture);
    _sprite.setPosition(_position);
    _sprite.setScale({GameConstants::SCALE_SIZE, GameConstants::SCALE_SIZE});

    sf::FloatRect bounds = _sprite.getGlobalBounds();
    _radius = std::max(bounds.size.x, bounds.size.y) / 2.0f;

    _ballOutline.setRadius(_radius);
    _ballOutline.setFillColor(sf::Color::Transparent);
    _ballOutline.setOutlineThickness(2.0f);
    _ballOutline.setOutlineColor(sf::Color::Red);
    _ballOutline.setPosition({ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f });
    IncreaseRadius(0);
}

void Ball::Update(Paddle& paddle)
{
    sf::FloatRect spriteBounds;
    if (!_isMoving) {
        sf::FloatRect paddleBounds = paddle.GetSprite().getGlobalBounds();
        float paddleCenterX = paddleBounds.position.x + (paddleBounds.size.x / 2.0f);
        _position.x = paddleCenterX - _texture.getSize().x;
        _position.y = paddleBounds.position.y - _texture.getSize().y * 2;

        _sprite.setPosition(_position);
        _ballOutline.setPosition({ _position.x, _position.y });

        if (isButtonPressed(sf::Mouse::Button::Left)) {
            _isMoving = true;
            _velocity = _initialVelocity;
        }
    } else {
        _sprite.move(_velocity * _speed);
        _ballOutline.setPosition(_sprite.getPosition());
    }
    spriteBounds = _sprite.getGlobalBounds();
    _ballOutline.setPosition({spriteBounds.position.x + spriteBounds.size.x / 2, spriteBounds.position.y + spriteBounds.size.y / 2});
}

void Ball::Draw(GameWindow &window)
{
    window.Draw(_sprite);
    window.Draw(_ballOutline);
}

void Ball::IncreaseRadius(float radius)
{ 
    _radius += radius; 
    _ballOutline.setRadius(_radius); 
    _ballOutline.setRadius(_radius);
        
    sf::FloatRect spriteBounds = _sprite.getGlobalBounds();
    _ballOutline.setOrigin({_radius, _radius});
    _ballOutline.setPosition({spriteBounds.position.x + spriteBounds.size.x / 2, spriteBounds.position.y + spriteBounds.size.y / 2}); 
}

void Ball::CheckWallCollisions(Paddle& paddle)
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
        _isMoving = false;
        _position = _initialPosition;
        _velocity = _initialVelocity;
        _sprite.setPosition(_position);

        float paddleCenterX = (_windowWidth - paddle.GetSprite().getGlobalBounds().size.x) / 2.0f;
        paddle.GetSprite().setPosition({paddleCenterX, paddle.GetSprite().getPosition().y});

    }
    _sprite.setPosition(pos);
    IncreaseRadius(0);
}

void Ball::ChangeDirection()
{
    float angle = (float)(rand() % 360);
    _velocity = { _speed * std::cos(angle), _speed * std::sin(angle) };
}

void Ball::CheckCollisions(Paddle& paddle, std::vector<std::shared_ptr<Brick>>& bricks) {
    CheckPaddleCollision(paddle);
    CheckBrickCollision(bricks);
    CheckWallCollisions(paddle);
}

void Ball::CheckPaddleCollision(Paddle& paddle) {
    sf::FloatRect ballBounds = GetBounds();
    sf::FloatRect paddleBounds = paddle.GetSprite().getGlobalBounds();

    if (ballBounds.findIntersection(paddleBounds)) {
        float hitPosition = (ballBounds.position.x + ballBounds.size.x/2 - paddleBounds.position.x) / paddleBounds.size.x;

        float angle = (hitPosition - 0.5f) * 120.0f;
        float radian = angle * 3.14159f / 180.0f;

        float speed = std::sqrt(_velocity.x * _velocity.x + _velocity.y * _velocity.y);
        _velocity.x = speed * std::sin(radian);
        _velocity.y = -std::abs(speed * std::cos(radian));

        _sprite.setPosition({ _sprite.getPosition().x, paddleBounds.position.y - ballBounds.size.y });
    }
}

void Ball::CheckBrickCollision(std::vector<std::shared_ptr<Brick>>& bricks) {
    sf::FloatRect ballBounds = GetBounds();

    for (auto& brick : bricks) {
        if (brick->IsDestroyed()) continue;

        sf::FloatRect brickBounds = brick->CreateSprite().getGlobalBounds();
        if (ballBounds.findIntersection(brickBounds)) {
            float overlapLeft = ballBounds.position.x + ballBounds.size.x - brickBounds.position.x;
            float overlapRight = brickBounds.position.x + brickBounds.size.x - ballBounds.position.x;
            float overlapTop = ballBounds.position.y + ballBounds.size.y - brickBounds.position.y;
            float overlapBottom = brickBounds.position.y + brickBounds.size.y - ballBounds.position.y;

            float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

            if (minOverlap == overlapLeft || minOverlap == overlapRight) {
                _velocity.x = -_velocity.x;
            } else {
                _velocity.y = -_velocity.y;
            }

            brick->OnCollision();
            break;
        }
    }
}