#pragma once
#include <bits/stdc++.h>
#include "../Core/IScene.h"
#include "../Entities/Food.h"
#include "../Entities/Snake.h"

class GameScene : public IScene
{
public: 
	GameScene(SoundManager* Sounds_);

	gameState handleInput(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;

	GameScene(const GameScene&) = delete;
	GameScene& operator = (const GameScene&) = delete;

	~GameScene() = default;

private:
	void resetGame();
	void updateGameState();
	gameState updateSnakeState();

	sf::Clock gameClock;
	Snake snake;
	Food food;
	float gameTimer = 0.f;
	float gameDelay = 0.1f;
};