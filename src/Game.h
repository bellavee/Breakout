
#ifndef GAME_H
#define GAME_H

#include "GameLevel.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameWindow.h"

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

private:
    int _currentLevel;
    int _currentScore;
    sf::Font _font;
    sf::Text _scoreText;
    sf::Text _levelText;
    std::unique_ptr<Paddle> _paddle;
    std::unique_ptr<Ball> _ball;
    std::unique_ptr<GameWindow> _gameWindow;
    std::vector<std::unique_ptr<GameLevel>> _allLevel;

    sf::Music _bgm;
    sf::Texture _bgTexture;
    sf::Sprite _bgSprite;

};



#endif //GAME_H
