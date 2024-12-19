
#include "Game.h"

Game::Game(int width, int height, const std::string& title) 
    : _gameWindow(std::make_unique<GameWindow>(width, height, title))
{
}

void Game::Init()
{
}

void Game::Run()
{
    std::unique_ptr<GameMap> map = std::make_unique<GameMap>(_gameWindow->GetWidth(), _gameWindow->GetHeight());
    map->LoadMap("../levels/1.txt");

    std::unique_ptr<Paddle> paddle = std::make_unique<Paddle>(_gameWindow->GetWidth(), _gameWindow->GetHeight());
    paddle->LoadImage("../assets/paddle.png");

    while (_gameWindow->IsOpen()) {
        while (const std::optional event = _gameWindow->PollEvent()) {
            if (event->is<sf::Event::Closed>())
                _gameWindow->Close();
        }
        _gameWindow->Clear(sf::Color::White);

        paddle->Update(*_gameWindow);

        map->Draw(*_gameWindow);
        paddle->Draw(*_gameWindow);

        _gameWindow->Display();
    }
}
