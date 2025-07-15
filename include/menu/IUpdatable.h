#pragma once

#include <SFML/Graphics.hpp>

class IUpdatable {
public:
    virtual void update(float dt) = 0;
    virtual ~IUpdatable() = default;
};