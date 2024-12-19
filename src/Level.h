
#ifndef LEVEL_H
#define LEVEL_H

#include "GameMap.h"
#include "GameWindow.h"

class Level {
public:
    Level();
    ~Level();

    void SetGameMap(std::unique_ptr<GameMap> map);
    void Update();
    void Draw(GameWindow& window);

private:
    std::unique_ptr<GameMap> _map;
};

#endif //LEVEL_H
