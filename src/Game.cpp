#include "../include/Game.h"

Game::Game() :
	window(VideoMode({ WIDTH, HEIGHT }), "Snake!"),
	timer(0), delay(0.1)
{
	font.openFromFile("C:/Windows/Fonts/Arial.ttf");
	food = Food(snake.getBody());
}

void Game::run()
{
	while (window.isOpen()) 
	{
		proccesEvents();
		ld dt = clock.restart().asSeconds();
		timer += dt;
		if (timer > delay)
		{
			timer = 0;
			snake.update(food, delay);
		}
		update();
		render();
	}
}
void Game::proccesEvents()
{
	while (const auto event = window.pollEvent())
	{
		if (event->is<Event::Closed>())
			window.close();
	}
	snake.handleInput();
}
void Game::update()
{
	if (snake.checkCollision())
		window.close();
	window.setTitle("Snake. Score: " + std::to_string(snake.getScore()));
}
void Game::render()
{
	window.clear(sf::Color::Black);
	snake.draw(window, timer / delay);
	food.draw(window);
	window.display();
}