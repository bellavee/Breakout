
#include "GameMap.h"


GameMap::GameMap(int windowWidth, int windowHeight)
    : _windowHeight(windowHeight)
    , _windowWidth(windowWidth)
{
}

GameMap::~GameMap()
{
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
    float startX = (_windowWidth - totalMapWidth) / 2.0f;
    float startY = (_windowHeight - totalMapHeight) / 10.0f;

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

void GameMap::Update(int &currentScore)
{
    _bricks.erase(
        std::remove_if(_bricks.begin(), _bricks.end(),
            [&currentScore](const std::shared_ptr<Brick>& brick) {
                if (brick->IsDestroyed())
                    currentScore += 10;
                return brick->IsDestroyed();
            }
        ),
        _bricks.end()
    );
}

void GameMap::Draw(GameWindow& window) 
{
    for (const std::shared_ptr<Brick>& brick : _bricks)
        brick->Draw(window);
}

void GameMap::RemoveBrick(std::shared_ptr<Brick> brick) {
    auto it = std::find(_bricks.begin(), _bricks.end(), brick);
    if (it != _bricks.end()) {
        _bricks.erase(it);
    }
}