
#ifndef BRICK_H
#define BRICK_H
#include "Breakout.h"

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

    void LoadImage(const std::string& filename);
    sf::Sprite CreateSprite();
    int GetTextureScaleSizeX() const { return _texture.getSize().x * GameConstants::SCALE_SIZE; }
    int GetTextureScaleSizeY() const { return _texture.getSize().y * GameConstants::SCALE_SIZE; }

    void Draw();
    void Update();
    void CheckCollision();
    void OnCollision();
    void OnStateChange();
    void SetState(BrickState state);
    bool IsDestroyed() const { return _isDestroy; }

private:
    sf::Vector2f _position;
    int _hitPoints;
    BrickState _state;
    bool _isDestroy = false;

    sf::Texture _texture;
};



#endif //BRICK_H
