
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
    void Run();
private:
    void LaunchNextLevel();
    void Win();
    void Lose();
    void Update();

private:
    int _currentLevel;
    int _currentScore;
    std::unique_ptr<Paddle> _paddle;
    std::unique_ptr<Ball> _ball;
    std::unique_ptr<GameWindow> _gameWindow;
    std::vector<std::unique_ptr<GameLevel>> _allLevel;
};



#endif //GAME_H
