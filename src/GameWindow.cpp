
#include "GameWindow.h"

GameWindow::GameWindow(int width, int height, const std::string &title) 
	: _width(width)
	, _height(height)
	, _window(sf::VideoMode({ (unsigned int)width, (unsigned int)height }), title)
{
	_window.setFramerateLimit(120);
	_window.setMouseCursorVisible(false);
}

GameWindow::~GameWindow()
{
}

void GameWindow::Display()
{
	_window.display();
}

int GameWindow::GetWidth()
{
	return _width;
}

int GameWindow::GetHeight()
{
	return _height;
}

bool GameWindow::IsOpen()
{
	return _window.isOpen();
}

void GameWindow::Close()
{
	_window.close();
}

void GameWindow::Clear(sf::Color color)
{
	_window.clear(color);
}

sf::RenderWindow &GameWindow::GetGameWindow()
{
    return _window;
}

std::optional<sf::Event> GameWindow::PollEvent()
{
	return _window.pollEvent();
}
