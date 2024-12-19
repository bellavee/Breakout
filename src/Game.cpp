
#include "Game.h"

Game::Game(int width, int height, const std::string& title) 
    : _font()
    , _scoreText(_font)
    , _gameClock()
    , _gameWindow(std::make_unique<GameWindow>(width, height, title))
    , _bgTexture()
    , _bgSprite(_bgTexture)
    , _paddle(std::make_unique<Paddle>("../assets/paddle.png", width, height))
    , _ball(std::make_unique<Ball>("../assets/ball.png", width, height, 2.0f, sf::Vector2f{(float) width / 2, (float) height / 2}, sf::Vector2f{2.0f, -2.0f}))
{
    if (!_bgTexture.loadFromFile("../assets/bg.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }

    sf::Sprite tmp(_bgTexture);
    _bgSprite = tmp;
    _bgSprite.setTexture(_bgTexture);

    _allLevel.push_back(std::make_unique<GameLevel>("../levels/1.txt", width, height));
    _allLevel.push_back(std::make_unique<GameLevel>("../levels/2.txt", width, height));
    _allLevel.push_back(std::make_unique<GameLevel>("../levels/3.txt", width, height));
    
    if (!_font.openFromFile("../assets/font/GeistMono-Bold.ttf"))
        throw std::runtime_error("Failed to load font");
    _scoreText.setFont(_font);
    _scoreText.setPosition({width - 200.0f, 10.0f});
    _scoreText.setFillColor(sf::Color::Black);
}

void Game::Init()
{
    srand(time(0));
    _currentLevel = 0;
    _currentScore = 0;
    _scoreText.setString("Score: " + std::to_string(_currentScore));

    if (!_bgm.openFromFile("../assets/bgm.mp3")) {
        std::cerr << "Failed to load background music!" << std::endl;
        return;
    }
    _bgm.setLooping(true);
    _bgm.setVolume(10.0f);
    _bgm.play();

    InitBonuses();
    InitMaluses();
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
        _gameWindow->Draw(_bgSprite);

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

    // launch new bonus
    if (_gameClock.getElapsedTime().asSeconds() >= 30.0f) {
        _gameClock.restart();
        int max = _bonuses.size();
        int i =  rand() % max;
        _bonuses[i]->Apply();
    }

    for (const auto & bonus : _bonuses)
        bonus->Update();
    for (const auto & malus : _maluses)
        malus->Update();
}

void Game::InitBonuses()
{
    auto paddleExpandEffect = [](Paddle& p) { p.IncreaseSize(2.5, 1.5); };
    auto paddleExpandResetEffect = [](Paddle& p) { p.DecreaseSize(2.5, 1.5); };
    auto ballExpandEffect = [](Ball& b) { b.IncreaseRadius(30.0); };
    auto ballExpandResetEffect = [](Ball& b) { b.IncreaseRadius(-30.0); };

    _bonuses.push_back(std::make_unique<GameEffect<Paddle>>("Expanding Paddle", paddleExpandEffect, paddleExpandResetEffect, *_paddle, 15.0f));
    _bonuses.push_back(std::make_unique<GameEffect<Ball>>("Fireball", ballExpandEffect, ballExpandResetEffect, *_ball, 15.0f));
}

void Game::InitMaluses()
{
}
