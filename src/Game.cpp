#include "../include/Game.h"

Game::Game() :
	window(VideoMode({ WIDTH, HEIGHT }), "Snake!"),
	timer(0), delay(0.1)
{
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
		snake.handleInput();
		if (Keyboard::isKeyPressed(Keyboard::Key::R))
			reset();
	}
}
void Game::update()
{
	if (snake.checkCollision())
		window.close();
	window.setTitle("Snake. Score: " + to_string(snake.getScore()));
}
void Game::render()
{
	window.clear(Color::Black);
	snake.draw(window, timer / delay);
	food.draw(window);
	window.display();
}
void Game::reset()
{
	snake = Snake();
	food = Food(snake.getBody());
	timer = 0;
	delay = 0.1;
}