
#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <vector>

#include "Brick.h"


class GameMap {
public:
    GameMap();
    ~GameMap();

    void Draw();
    void RemoveBrick(Brick* brick);

private:
    std::vector<Brick*> _bricks;

};



#endif //GAMEMAP_H
