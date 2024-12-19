#ifndef  _I_GAME_EFFECT_
#define _I_GAME_EFFECT_

class IGameEffect
{
public:
    virtual ~IGameEffect() = default;
    virtual void Apply() = 0;
    virtual void Reset() = 0;
    virtual void Update() = 0;
};

#endif