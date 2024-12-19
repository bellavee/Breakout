#ifndef  _GAME_EFFECT_
#define _GAME_EFFECT_

#include "Breakout.h"
#include "IGameEffect.h"

template <typename T>

class GameEffect : public IGameEffect
{
public:
    GameEffect(const std::string& name, std::function<void(T&)> effect, 
        std::function<void(T&)> effectReset, T& target, float effectDuration) 
        : _name(name)
        , _duration(effectDuration)
        , _target(target)
        , _timer()
        , _effect(effect)
        , _effectReset(effectReset)
    {
    }

    void Apply() override
    {
        if (_isRunning)
            return;
        _effect(_target);
        _isRunning = true;
        _timer.restart();
    }

    void Reset() override
    {
        if (!_isRunning)
            return;
        _effectReset(_target);
        _isRunning = false;
        _timer.reset();
    }

    void Update() override
    {
        if (!_isRunning)
            return;
        if (_timer.getElapsedTime().asSeconds() >= _duration && _isRunning) {
            Reset();
        }
    }

    std::string GetName() override
    {
        return _name;
    }

    bool IsRunning() override
    {
        return _isRunning;
    }

private:
    bool _isRunning = false;
    float _duration;
    T &_target;
    sf::Clock _timer;
    std::string _name;
    std::function<void(T&)> _effect;
    std::function<void(T&)> _effectReset;
};

#endif