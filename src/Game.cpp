
#include "Game.h"

Game::Game(int width, int height, const std::string& title) 
    : _font()
    , _scoreText(_font)
    , _bonusClock()
    , _malusClock()
    , _levelText(_font)
    , _malusText(_font)
    , _bonusText(_font)
    , _gameWindow(std::make_unique<GameWindow>(width, height, title))
    , _bgTexture()
    , _bgSprite(_bgTexture)
    , _paddle(std::make_unique<Paddle>("../assets/paddle.png", width, height))
    , _ball(std::make_unique<Ball>("../assets/ball.png", width, height, 2.0f, sf::Vector2f{(float)width / 2, (float)height - 100.0f}, sf::Vector2f{2.5f, -2.5f}))
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

    _bonusText.setFont(_font);
    _bonusText.setPosition({200.0f, 15.0f});
    _bonusText.setFillColor(sf::Color::Black);
    _bonusText.setCharacterSize(20);

    _malusText.setFont(_font);
    _malusText.setPosition({650.0f, 15.0f});
    _malusText.setFillColor(sf::Color::Black);
    _malusText.setCharacterSize(20);

    _levelText.setFont(_font);
    _levelText.setPosition({10.0f, 10.0f});
    _levelText.setFillColor(sf::Color::Black);
}

void Game::Init()
{
    srand(time(0));
    _currentLevel = 0;
    _currentScore = 0;
    _scoreText.setString("Score: " + std::to_string(_currentScore));
    _levelText.setString("Score: " + std::to_string(_currentLevel + 1));

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
        _ball->Update(*_paddle);
        _ball->CheckCollisions(*_paddle, _allLevel[_currentLevel]->GetMap()->GetBricks());

        _gameWindow->Clear(sf::Color::White);
        _gameWindow->Draw(_bgSprite);
        _allLevel[_currentLevel]->Draw(*_gameWindow);
        _paddle->Draw(*_gameWindow);
        _ball->Draw(*_gameWindow);
        _gameWindow->Draw(_scoreText);
        _gameWindow->Draw(_levelText);
        _gameWindow->Draw(_malusText);
        _gameWindow->Draw(_bonusText);

        _gameWindow->Display();
    }
}

void Game::LaunchNextLevel()
{
    if (_currentLevel + 1 < _allLevel.size()) {
        _currentLevel++;
    }

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
    std::string bonusStr("None"), malusStr("None");
    if (_allLevel[_currentLevel]->GetLevelStatus() == LevelStatus::Ended)
        LaunchNextLevel();

    if (_bonusClock.getElapsedTime().asSeconds() >= 30.0f) {
        _bonusClock.restart();
        int max = _bonuses.size();
        int i =  rand() % max;
        _bonuses[i]->Apply();
    }

    if (_malusClock.getElapsedTime().asSeconds() >= 45.0f) {
        _malusClock.restart();
        int max = _maluses.size();
        int i =  rand() % max;
        _maluses[i]->Apply();
    }

    for (const auto & bonus : _bonuses) {
        bonus->Update();
        if (bonus->IsRunning())
            bonusStr =  bonus->GetName();
    }
    for (const auto & malus : _maluses) {
        malus->Update();
        if (malus->IsRunning())
            malusStr =  malus->GetName();
    }

    _scoreText.setString("Score: " + std::to_string(_currentScore));
    _levelText.setString("Level: " + std::to_string(_currentLevel + 1));
    _bonusText.setString("Current Bonus: " + bonusStr);
    _malusText.setString("Current Malus: " + malusStr);
}

void Game::InitBonuses()
{
    auto paddleExpandEffect = [](Paddle& p) { p.IncreaseSize(2.5, 1.5); };
    auto paddleExpandResetEffect = [](Paddle& p) { p.DecreaseSize(2.5, 1.5); };
    auto ballExpandEffect = [](Ball& b) { b.IncreaseRadius(30.0); };
    auto ballExpandResetEffect = [](Ball& b) { b.IncreaseRadius(-30.0); };
    auto speedBoostEffect = [](Ball& b) { b.IncreaseSpeed(-1); };
    auto speedResetEffect = [](Ball& b) { b.IncreaseSpeed(1); };

    _bonuses.push_back(std::make_unique<GameEffect<Paddle>>("Expanding Paddle", paddleExpandEffect, paddleExpandResetEffect, *_paddle, 15.0f));
    _bonuses.push_back(std::make_unique<GameEffect<Ball>>("Fireball", ballExpandEffect, ballExpandResetEffect, *_ball, 15.0f));
    _bonuses.push_back(std::make_unique<GameEffect<Ball>>("Slow Motion", speedBoostEffect, speedResetEffect, *_ball, 15.0f));
}

void Game::InitMaluses()
{
    auto paddleSrinkEffect = [](Paddle& p) { p.DecreaseSize(1.5, 0.5); };
    auto paddleSrinkResetEffect = [](Paddle& p) { p.IncreaseSize(1.5, 0.5); };
    auto speedBoostEffect = [](Ball& b) { b.IncreaseSpeed(2); };
    auto speedResetEffect = [](Ball& b) { b.IncreaseSpeed(-2); };

    _maluses.push_back(std::make_unique<GameEffect<Paddle>>("Shrinking Paddle", paddleSrinkEffect, paddleSrinkResetEffect, *_paddle, 15.0f));
    _maluses.push_back(std::make_unique<GameEffect<Ball>>("Speed Up", speedBoostEffect, speedResetEffect, *_ball, 15.0f));
}
