#pragma once

#include <SFML/Graphics.hpp>

class IRenderable {
public:
    virtual void draw(sf::RenderWindow&) = 0;
    virtual ~IRenderable() = default;
};