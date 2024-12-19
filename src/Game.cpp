
#include "Game.h"

Game::Game(int width, int height, const std::string& title) 
    : _gameWindow(std::make_unique<GameWindow>(width, height, title))
    , _paddle(std::make_unique<Paddle>(width, height))
{
    _allLevel.push_back(std::make_unique<GameLevel>("../levels/1.txt", width, height));
    _paddle->LoadImage("../assets/paddle.png");
}

void Game::Init()
{
    _currentLevel = 0;
    _currentScore = 0;
}

void Game::Run()
{
    while (_gameWindow->IsOpen()) {
        while (const std::optional event = _gameWindow->PollEvent()) {
            if (event->is<sf::Event::Closed>())
                _gameWindow->Close();
        }
        Update();
        _allLevel[_currentLevel]->Update(*_gameWindow, _currentScore);
        _paddle->Update(*_gameWindow);
        
        _gameWindow->Clear(sf::Color::White);
        _allLevel[_currentLevel]->Draw(*_gameWindow);
        _paddle->Draw(*_gameWindow);

        _gameWindow->Display();
    }
}

void Game::LaunchNextLevel()
{
    if (_currentLevel + 1 < _allLevel.size())
        _currentLevel++;
    else
        Win();
}

void Game::Win()
{
}

void Game::Lose()
{
}

void Game::Update()
{
    switch (_allLevel[_currentLevel]->GetLevelStatus()) {
        case LevelStatus::Win :
            LaunchNextLevel();
            break;
        case LevelStatus::Lose :
            Lose();
            break;
        default:
            break;
        }
}
