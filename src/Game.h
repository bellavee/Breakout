
#ifndef GAME_H
#define GAME_H

#include "Level.h"
#include "Paddle.h"
#include "GameWindow.h"

class Game {
public:
    Game(int width, int height, const std::string &title);
    void Init();
    void Run();
    void CreatePlayer();
    void LauchNextLevel();
    void Win();
    void Lose();

private:
    int _currentLevel;
    int _currentScore;
    std::unique_ptr<GameWindow> _gameWindow;
};



#endif //GAME_H
