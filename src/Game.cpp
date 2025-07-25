#include "../include/Game.h"

namespace {
	constexpr float INITIAL_DELAY = 0.1f;
	const std::string WINDOW_TITLE = "Snake Game";
}

Game::Game(sf::Image& icon) :
	window(sf::VideoMode({ WIDTH, HEIGHT }), WINDOW_TITLE),
	snake(),
	food(snake.getBody())
{
	window.setIcon({ icon.getSize() }, icon.getPixelsPtr());
	food.loadEatSound();
}

void Game::run()
{
	while (window.isOpen()) 
	{
		proccesEvents();
		const float deltaTime = gameClock.restart().asSeconds();
		updateGameState(deltaTime);
		update();
		render();
	}
}

void Game::updateGameState(float deltaTime)
{
	gameTimer += deltaTime;
	if (gameTimer > gameDelay)
	{
		gameTimer = 0.0f;
		snake.update(food, gameDelay);
	}

}
void Game::proccesEvents()
{
	while (const auto event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window.close();
		snake.handleInput();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
			reset();
	}
}
void Game::update()
{
	if (snake.checkCollision())
		window.close();
	window.setTitle(WINDOW_TITLE + " Score: " + std::to_string(snake.getScore()));
}
void Game::render()
{
	window.clear(sf::Color::Black);
	snake.draw(window, gameTimer / gameDelay);
	food.draw(window);
	window.display();
}
void Game::reset()
{
	snake.reset();
	food.respawn(snake.getBody());
	gameTimer = 0.f;
	gameDelay = INITIAL_DELAY;
}