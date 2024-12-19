#include "GameLevel.h"
#include "GameLevel.h"

GameLevel::GameLevel(std::string mapFilePath, int windowWidth, int windowHeight) 
    : _map(std::make_unique<GameMap>(windowWidth, windowHeight))
{
    _map->LoadMap("../levels/1.txt");
}

void GameLevel::Update(GameWindow &windox, int &currentScore)
{
}

void GameLevel::Draw(GameWindow &window)
{
    _map->Draw(window);
}

LevelStatus GameLevel::GetLevelStatus()
{
    return LevelStatus::Running;
}
