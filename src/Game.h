
#ifndef GAME_H
#define GAME_H

#include "GameLevel.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameWindow.h"
#include "GameEffect.h"

class Game {
public:
    Game(int width, int height, const std::string &title);
    void Init();

    void InitBackground(int width, int height);

    void Run();
private:
    void LaunchNextLevel();
    void Win();
    void Lose();
    void Update();
    void InitBonuses();
    void InitMaluses();

private:
    int _currentLevel;
    int _currentScore;
    sf::Font _font;
    sf::Text _scoreText;
    std::unique_ptr<Paddle> _paddle;
    std::unique_ptr<Ball> _ball;
    std::unique_ptr<GameWindow> _gameWindow;
    std::vector<std::unique_ptr<GameLevel>> _allLevel;
    std::vector<std::unique_ptr<IGameEffect>> _bonuses;
    std::vector<std::unique_ptr<IGameEffect>> _maluses;

    sf::Music _bgm;
    sf::Texture _bgTexture;
    sf::Sprite _bgSprite;
    sf::Clock _gameClock;
};



#endif //GAME_H
