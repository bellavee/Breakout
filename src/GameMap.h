
#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <vector>

#include "Brick.h"


namespace sf {
    class RenderWindow;
}

class GameMap {
public:
    GameMap(sf::RenderWindow &window);
    ~GameMap();

    void LoadMap(const std::string& filename);
    void Draw();
    void RemoveBrick(std::shared_ptr<Brick> brick);
    bool IsComplete() const { return _bricks.empty(); }


private:
    std::vector<std::shared_ptr<Brick>> _bricks;
    sf::RenderWindow& _window;

    void Clear();

};



#endif //GAMEMAP_H
