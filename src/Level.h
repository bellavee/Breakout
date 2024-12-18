
#ifndef LEVEL_H
#define LEVEL_H
#include "GameMap.h"


class Level {
public:
    Level();
    ~Level();

    void Initialize(std::unique_ptr<GameMap> map);
    void CheckGameState();

private:
    std::unique_ptr<GameMap> _map;

};



#endif //LEVEL_H
