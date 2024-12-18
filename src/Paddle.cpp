
#include "Paddle.h"

Paddle::Paddle(sf::RenderWindow& window) : _window(window), _speed(PADDLE_SPEED),
                                           _windowWidth(window.getSize().x) {
    _position.x = _window.getSize().x / 2.0f;
    _position.y = _window.getSize().y - 100.0f;
}

Paddle::~Paddle() {
}

void Paddle::LoadImage(const std::string &filename) {
}

void Paddle::Update() {
}

void Paddle::Draw() {
}

void Paddle::HandleKeyboardInput() {
}

void Paddle::HandleMouseInput() {
}
