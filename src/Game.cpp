
#include "Game.h"

Game::Game(int width, int height, const std::string& title) 
    : _font()
    , _scoreText(_font)
    , _gameWindow(std::make_unique<GameWindow>(width, height, title))
    , _paddle(std::make_unique<Paddle>(width, height))
    , _ball(std::make_unique<Ball>("../assets/ball.png", width, height, 2.0f, sf::Vector2f{(float) width / 2,(float)height / 2}, sf::Vector2f{2.0f, -2.0f}))
{
    _allLevel.push_back(std::make_unique<GameLevel>("../levels/1.txt", width, height));
    _allLevel.push_back(std::make_unique<GameLevel>("../levels/2.txt", width, height));
    _allLevel.push_back(std::make_unique<GameLevel>("../levels/3.txt", width, height));
    _paddle->LoadImage("../assets/paddle.png");
    
    if (!_font.openFromFile("../assets/font/GeistMono-Bold.ttf"))
        throw std::runtime_error("Failed to load font");
    _scoreText.setFont(_font);
    _scoreText.setPosition({width - 200.0f, 10.0f});
    _scoreText.setFillColor(sf::Color::Black);
}

void Game::Init()
{
    _currentLevel = 0;
    _currentScore = 0;
    _scoreText.setString("Score: " + std::to_string(_currentScore));
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
        _ball->Update();
        _scoreText.setString("Score: " + std::to_string(_currentScore));
        _ball->CheckCollisions(*_paddle, _allLevel[_currentLevel]->GetMap()->GetBricks());

        _gameWindow->Clear(sf::Color::White);
        _allLevel[_currentLevel]->Draw(*_gameWindow);
        _paddle->Draw(*_gameWindow);
        _ball->Draw(*_gameWindow);
        _gameWindow->Draw(_scoreText);

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
    if (_allLevel[_currentLevel]->GetLevelStatus() == LevelStatus::Ended)
        LaunchNextLevel();
}
