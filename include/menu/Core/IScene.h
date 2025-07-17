#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "../Constants.h"
#include "SoundManager.h"

class IScene
{
public:
	IScene(SoundManager* Sounds_) : Sounds(Sounds_) {}
	virtual gameState handleInput(sf::RenderWindow& window) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	virtual ~IScene() = default;
protected:
	SoundManager* Sounds;
};