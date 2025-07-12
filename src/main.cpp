#include <bits/stdc++.h>
#include "../include/Game.h"
#include "../include/menu/Menu.h";

int main()
{
	sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Snake!");
	sf::Image icon("./resources/icon.png");
	window.setIcon(icon);
	sf::Font font("./resources/fonts/arial.ttf");
	sf::Texture back("./resources/background.jpg");
	Menu menu(WIDTH, HEIGHT, font, back);
	enum class gameState { MenuWin, SettingsWin, GameWin };
	gameState currentState = gameState::MenuWin;
	while (window.isOpen())
	{
		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();

			if (currentState != gameState::GameWin)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
				{
					menu.moveUp();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
				{
					menu.moveDown();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
				{
					menu.playConfirmSound();
					/*if (menu.getSelectedIndex() == 0)
					{
						currentState = gameState::GameWin;
					}
					else if (menu.getSelectedIndex() == 2)
					{
						window.close();
					}*/
					switch (menu.getSelectedIndex())
					{
					case 0:
						currentState = gameState::GameWin;
						break;
					case 1:
						currentState = gameState::SettingsWin;
						break;
					case 2:
						window.close();
					}
				}
			}
		}

		window.clear(sf::Color::Black);
		switch (currentState)
		{
		case gameState::MenuWin:
			menu.draw(window);
			break;
		case gameState::SettingsWin:
			menu.drawSettings(window);
			break;
		case gameState::GameWin:
			Game game(icon);
			game.run();
			currentState = gameState::MenuWin;
			break;
		}
		window.display();
	}

	return 0;
}