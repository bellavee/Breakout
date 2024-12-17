
#ifndef GAME_H
#define GAME_H



class Game {
public:
    Game();
    ~Game();

    void Initialize();
    void Run();
    void CreatePlayer();
    void SwitchLevel();
    void Win();
    void Lose();

private:
    int _currentLevel;
    int _currentScore;

};



#endif //GAME_H
