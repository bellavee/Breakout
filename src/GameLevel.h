
#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "GameMap.h"
#include "GameWindow.h"

enum class LevelStatus {
    Running,
    Win,
    Lose,
};

class GameLevel {
public:
    GameLevel(std::string mapFilePath, int windowWidth, int windowHeight);
    void Update(GameWindow &windox, int &currentScore);
    void Draw(GameWindow& window);
    LevelStatus GetLevelStatus();
private:
    std::unique_ptr<GameMap> _map;
};

#endif //LEVEL_H
