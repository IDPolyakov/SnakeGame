#include "../../include/Scenes/MainMenu.h"

MainMenu::MainMenu(float width, float height, const sf::Font& font, const sf::Texture& back, SoundManager* Sounds_)
	:
	IMenu(width, height, font, back),
	IScene(Sounds_)
{ 
	Sounds->playMusic("backMenuMusic");
	initializeMenuItems(width, height, font);
	initializeTitle(width, height);
}

void MainMenu::initializeMenuItems(float width, float height, const sf::Font& font)
{
	const std::vector<std::string > menuItemLabels = {
		"Play",
		"Settings",
		"Exit"
	};
	for (size_t i = 0; i < menuItemLabels.size(); i++)
	{
		sf::Text text(font, menuItemLabels[i]);

		const bool isSelected = (i == selectedIndex);
		text.setFillColor(i == selectedIndex ? SELECTED_COLOR : UNSELECTED_COLOR);
		text.setOutlineColor(OUTLINE_COLOR);
		text.setOutlineThickness(OUTLINE_THICKNESS);
		text.setCharacterSize(isSelected ? SELECTED_CHAR_SIZE : UNSELECTED_CHAR_SIZE);

		const float xPosition = static_cast<float>(width) / 2.f - MENU_ITEM_X_OFFSET;
		const float yPosition = static_cast<float>(height) / MENU_ITEM_Y_START + i * MENU_ITEM_Y_OFFSET;
		text.setPosition({ xPosition, yPosition });
		menuItems.push_back(text);
	}
}

void MainMenu::initializeTitle(float width, float height)
{
	title.setString("Snake Game");
	title.setCharacterSize(TITLE_CHAR_SIZE);
	title.setFillColor(TITLE_COLOR);
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);

	const float xPosition = static_cast<float>(width) / 2.0f - TITLE_X_OFFSET;
	const float yPosition = static_cast<float>(height) / MENU_ITEM_Y_START - TITLE_Y_OFFSET;
	title.setPosition({ xPosition, yPosition });
}
void MainMenu::updateMenuItemsAnimation()
{
	const float time = static_cast<float>(clock.getElapsedTime().asMilliseconds());
	const float scale = 1.f + ANIMATION_SCALE * sin(time * ANIMATION_SPEED);

	for (size_t i = 0; i < menuItems.size(); i++)
	{
		if (i == selectedIndex)
			menuItems[i].setScale({ scale, scale });
		else
			menuItems[i].setScale({ 1.f, 1.f });
	}
}

void MainMenu::render(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(title);

	updateMenuItemsAnimation();
	for (const auto& item : menuItems)
		window.draw(item);
}

gameState MainMenu::handleInput(sf::RenderWindow& window)
{
	while (const auto event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			Sounds->playSound("choice");
			moveUp();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			Sounds->playSound("choice");
			moveDown();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		{
			Sounds->playSound("confirm");
			switch (getSelectedIndex())
			{
			case 0:
				std::clog << "MainMenu play button pressed\n";
				Sounds->stopMusic("backMenuMusic");
				return gameState::GameWindow;
				break;
			case 1:
				std::clog << "MainMenu settings button pressed\n";
				return gameState::SettingsWindow;
				break;
			case 2:
				std::clog << "MainMenu exit button pressed\n";
				return gameState::Exit;
				break;
			}
		}
	}
}