#include "Game.h"

int main() {
    Game breakout(1280, 720, "Breakout");
    breakout.Init();
    breakout.Run();
    return 0;
}
