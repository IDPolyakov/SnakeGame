#include <bits/stdc++.h>
#include "../include/Scenes/MainMenu.h"
#include "../include/Scenes/SettingsMenu.h"
#include "../include/Scenes/GameScene.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Snake!");

	sf::Image icon("./resources/icon.png");
	window.setIcon(icon);

	sf::Font font("./resources/fonts/arial.ttf");
	sf::Texture back("./resources/background.jpg");

	std::unique_ptr<SoundManager> Sounds_(new SoundManager);

	std::map<std::string, std::shared_ptr<IScene>> states;
	states["Menu"].reset(new MainMenu(WIDTH, HEIGHT, font, back, Sounds_.get()));
	states["Settings"].reset(new SettingsMenu(WIDTH, HEIGHT, font, back, Sounds_.get()));

	std::shared_ptr<IScene> current = states["Menu"];

	gameState currentState;

	bool isPlaying = false;

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		currentState = current->handleInput(window);
		switch (currentState)
		{
		case gameState::Back:
			Sounds_->playMusic("backMenuMusic");
			current = states["Menu"];
			isPlaying = false;
			break;
		case gameState::SettingsWindow:
			_Thrd_sleep_for(100);
			current = states["Settings"];
			break;
		case gameState::Exit:
			window.close();
			break;
		case gameState::GameWindow:
			if (!isPlaying)
			{
				Sounds_->playMusic("backGameMusic");
				current.reset(new GameScene(Sounds_.get()));
				isPlaying = true;
			}
			break;
		}

		current->render(window);

		window.display();
	}

	return 0;
}