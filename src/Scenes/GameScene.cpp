#include "../../include/Scenes/GameScene.h"

GameScene::GameScene(SoundManager* Sounds_)
	:
	IScene(Sounds_),
	snake(), 
	food(snake.getBody(), Sounds_)
{
}

gameState GameScene::handleInput(sf::RenderWindow& window)
{
	while (const auto event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window.close();
		snake.handleInput();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
			resetGame();
	}
	updateGameState();
	return updateSnakeState();
}

void GameScene::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	snake.draw(window, gameTimer / gameDelay);
	food.draw(window);
}

void GameScene::resetGame()
{
	snake.reset();
	food.respawn(snake.getBody());
	gameTimer = 0.0f;
	gameDelay = 0.1f;
}

void GameScene::updateGameState()
{
	gameTimer += gameClock.restart().asSeconds();
	if (gameTimer > gameDelay)
	{
		gameTimer = 0.f;
		snake.update(food, gameDelay);
	}
}

gameState GameScene::updateSnakeState()
{
	if (snake.checkCollision())
	{
		Sounds->stopMusic("backGameMusic");
		return gameState::Back;
	}
	return gameState::GameWindow;
}