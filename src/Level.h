
#ifndef LEVEL_H
#define LEVEL_H
#include "GameMap.h"


class Level {
public:
    Level();
    ~Level();

    void Initialize(GameMap* map);
    void CheckGameState();

private:
    GameMap* _map;

};



#endif //LEVEL_H
