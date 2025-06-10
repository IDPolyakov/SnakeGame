#include <bits/stdc++.h>
#include "../include/Game.h"
#include "../include/menu/Menu.h";
using namespace std;

int main()
{
	RenderWindow window(VideoMode({ WIDTH, HEIGHT }), "Snake!");
	Image icon("./resources/icon.png");
	window.setIcon(icon);
	Font font("./resources/fonts/arial.ttf");
	Texture back("./resources/background.jpg");
	Menu menu(WIDTH, HEIGHT, font, back);
	bool gameRunning = false;
	while (window.isOpen())
	{
		while (const auto event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();

			if (!gameRunning)
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::Up))
					menu.moveUp();
				else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
					menu.moveDown();
				else if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
				{
					if (menu.getSelectedIndex() == 0)
						gameRunning = true;
					else if (menu.getSelectedIndex() == 2)
						window.close();
				}
			}
		}

		window.clear(Color::Black);
		if (!gameRunning)
		{
			menu.draw(window);
		}
		else
		{
			Game game;
			game.run();
			gameRunning = false;
		}
		window.display();
	}

	return 0;
}