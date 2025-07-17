#include <bits/stdc++.h>
#include "../include/Game.h"
#include "../include/menu/MainMenu.h"
#include "../include/menu/SettingsMenu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Snake!");

	sf::Image icon("./resources/icon.png");
	window.setIcon(icon);

	sf::Font font("./resources/fonts/arial.ttf");
	sf::Texture back("./resources/background.jpg");

	std::unique_ptr<SoundManager> Sounds_(new SoundManager);

	std::unique_ptr<IScene> current(new MainMenu(WIDTH, HEIGHT, font, back, Sounds_.get()));

	gameState currentState;

	while (window.isOpen())
	{
		/*
		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();

			if (currentState != gameState::GameWindow)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
				{
					current->moveUp();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
				{
					current->moveDown();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
				{
					switch (current->getSelectedIndex())
					{
					case 0:
						currentState = gameState::GameWindow;
						break;
					case 1:
						currentState = gameState::SettingsWindow;
						current.reset(new SettingsMenu(WIDTH, HEIGHT, font, back));
						break;
					case 2:
						window.close();
					}
				}
			}
		}*/

		window.clear(sf::Color::Black);
		currentState = current->handleInput(window);
		switch (currentState)
		{
		case gameState::Back:
			current.reset(new MainMenu(WIDTH, HEIGHT, font, back, Sounds_.get()));
			break;
		case gameState::SettingsWindow:
			current.reset(new SettingsMenu(WIDTH, HEIGHT, font, back, Sounds_.get()));
			break;
		case gameState::Exit:
			window.close();
			break;
		case gameState::GameWindow:
			Game game(icon);
			game.run();
			break;
		}

		current->render(window);

		window.display();
	}

	return 0;
}