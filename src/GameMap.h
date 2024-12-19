
#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "Breakout.h"
#include "Brick.h"
#include "GameWindow.h"

class GameMap {
public:
    GameMap(int windowWidth, int windowHeight);
    ~GameMap();

    void LoadMap(const std::string& filename);
    void Update(int &currentScore);
    void Draw(GameWindow &window);
    void RemoveBrick(std::shared_ptr<Brick> brick);
    bool IsEmpty() const { return _bricks.empty(); }
    std::vector<std::shared_ptr<Brick>>& GetBricks() { return _bricks; }

private:
    std::vector<std::shared_ptr<Brick>> _bricks;
    int _windowWidth;
    int _windowHeight;

};



#endif //GAMEMAP_H
