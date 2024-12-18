
#ifndef BRICK_H
#define BRICK_H
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

enum BrickState {
    Destroy,
    Level1,
    Level2,
    Level3,
    Level4,
};

class Brick {
public:
    Brick(sf::Vector2f pos);
    ~Brick();

    auto LoadImage(std::filesystem::path filePath) -> void;
    sf::Sprite CreateSprite();

    void Draw();
    void Update();
    void CheckCollision();
    void OnCollision(sf::Vector2f dir);
    void OnStateChange();
    void SetState(BrickState state);

private:
    sf::Vector2f _position;
    int _hitPoints;
    BrickState _state;
    bool _isDestroy = false;

    sf::Texture _texture;
};



#endif //BRICK_H
