#ifndef BRICK_H
#define BRICK_H
#include "Breakout.h"
#include "GameWindow.h"

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
    void LoadCrackOverlay(const std::string& filename);
    sf::Sprite CreateSprite();
    void Draw(GameWindow& window);
    int GetTextureScaleSizeX() const { return _texture.getSize().x * GameConstants::SCALE_SIZE; }
    int GetTextureScaleSizeY() const { return _texture.getSize().y * GameConstants::SCALE_SIZE; }

    void OnCollision();
    void SetState(BrickState state);

    void LoadHitSound(const std::string &filename);
    void PlayHitSound();
    bool IsDestroyed() const { return _isDestroy; }

private:

    sf::Vector2f _position;
    int _hitPoints;
    BrickState _state;
    bool _isDestroy = false;

    sf::Texture _texture;
    sf::Texture _crackTexture;
    bool _hasCrack = false;

    sf::SoundBuffer _hitSoundBuffer;
    sf::Sound _hitSound;
    bool _soundLoaded = false;

};

#endif //BRICK_H