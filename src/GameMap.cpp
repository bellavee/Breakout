
#include "GameMap.h"

#include <fstream>

#include "SFML/Graphics/RenderWindow.hpp"

GameMap::GameMap(sf::RenderWindow& window) : _window(window) {
}

GameMap::~GameMap() {
    _bricks.clear();
}

void GameMap::LoadMap(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open level file: " + filename);
    }

    int mapWidth, mapHeight;
    file >> mapWidth >> mapHeight;

    std::shared_ptr<Brick> tmpBrick = std::make_shared<Brick>(sf::Vector2f(0, 0));
    tmpBrick->LoadImage("../assets/brick-1.png");

    float BRICK_WIDTH = tmpBrick->GetTextureScaleSizeX();
    float BRICK_HEIGHT = tmpBrick->GetTextureScaleSizeY();

    float totalMapWidth = mapWidth * BRICK_WIDTH + (mapWidth - 1);
    float totalMapHeight = mapHeight * BRICK_HEIGHT + (mapHeight - 1);
    float startX = (_window.getSize().x - totalMapWidth) / 2.0f;
    float startY = (_window.getSize().y - totalMapHeight) / 10.0f;

    for (int row = 0; row < mapHeight; row++) {
        std::string line;
        if (row == 0) std::getline(file >> std::ws, line);
        std::getline(file, line);

        for (int col = 0; col < mapWidth; col++) {
            if (col < line.length()) {
                int brickType = line[col] - '0';
                if (brickType > 0) {
                    float x = startX + col * BRICK_WIDTH;
                    float y = startY + row * BRICK_HEIGHT;

                    std::shared_ptr brick = std::make_unique<Brick>(sf::Vector2f(x, y));
                    brick->SetState(static_cast<BrickState>(brickType));
                    brick->LoadImage("../assets/brick-" + std::to_string(brickType) + ".png");

                    _bricks.push_back(brick);
                }
            }
        }
    }

}

void GameMap::Draw() {
    for (const std::shared_ptr brick : _bricks) {
        _window.draw(brick->CreateSprite());
    }
}

void GameMap::RemoveBrick(std::shared_ptr<Brick> brick) {

}
