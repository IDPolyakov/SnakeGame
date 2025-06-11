#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Food.h"
#include "Snake.h"
//❤//
using namespace std;
using namespace sf;

class Game
{
public:
	explicit Game(Image& icon);
	void run();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
private:
	void proccesEvents();
	void update();
	void render();
	void reset();
	void updateGameState(float deltaTime);

	RenderWindow window;
	Clock gameClock;
	Snake snake;
	Food food;
	float gameTimer = 0.f;
	float gameDelay = 0.1f;
};

