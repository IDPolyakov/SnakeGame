#include "../../include/Scenes/SettingsMenu.h"

SettingsMenu::SettingsMenu(float width, float height, const sf::Font& font, const sf::Texture& back, SoundManager* Sounds_) 
	:
	IMenu(width, height, font, back), 
	IScene(Sounds_)
{
	initializeMenuItems(width, height, font);
	initializePolygons(width, height);
	initializeParams(width, height, font);
	initializeTitle(width, height);
}

void SettingsMenu::initializeParams(float width, float height, const sf::Font& font)
{
	for (int i = 0; i < 2; i++)
	{
		textParams.push_back(sf::Text(font, std::to_string(params[i]),UNSELECTED_CHAR_SIZE ));
		const float xPosition = static_cast<float>(width) - MENU_ITEM_X_OFFSET * 1.5 - 75;
		const float yPosition = static_cast<float>(height) / MENU_ITEM_Y_START + i * MENU_ITEM_Y_OFFSET + 10;
		textParams[i].setPosition({xPosition, yPosition});
		textParams[i].setFillColor(sf::Color::Blue);
		textParams[i].setStyle(sf::Text::Bold);
	}
}

void SettingsMenu::initializePolygons(float width, float height)
{
	for (int i = 0; i < 2; i++)
	{
		sf::ConvexShape newPolygon(3);
		const float xPosition = static_cast<float>(width) - MENU_ITEM_X_OFFSET * 1.5;
		const float yPosition = static_cast<float>(height) / MENU_ITEM_Y_START + i * MENU_ITEM_Y_OFFSET + 20;
		newPolygon.setPoint(0, { 0, 0 });
		newPolygon.setPoint(1, { 0, 30});
		newPolygon.setPoint(2, { 40, 15 });
		newPolygon.setFillColor(sf::Color::Red);
		newPolygon.setOutlineThickness(2);
		newPolygon.setOutlineColor(sf::Color::Black);
		newPolygon.setPosition({ xPosition, yPosition });
		polygons.push_back(newPolygon);
		newPolygon.setPosition({ xPosition - 80, yPosition });
		newPolygon.setPoint(0, { 0, 0 });
		newPolygon.setPoint(1, { 0, 30 });
		newPolygon.setPoint(2, { -40, 15 });
		polygons.push_back(newPolygon);

	}
}

void SettingsMenu::initializeMenuItems(float width, float height, const sf::Font& font)
{
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


void SettingsMenu::initializeTitle(float width, float height)
{
	title.setString("Settings");
	title.setCharacterSize(TITLE_CHAR_SIZE);
	title.setFillColor(TITLE_COLOR);
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);

	const float xPosition = static_cast<float>(width) / 2.0f - TITLE_X_OFFSET + 70;
	const float yPosition = static_cast<float>(height) / MENU_ITEM_Y_START - TITLE_Y_OFFSET;
	title.setPosition({ xPosition, yPosition });
}

void SettingsMenu::updateMenuItemsAnimation()
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

void SettingsMenu::render(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(title);

	for (const auto& option : menuItems)
	{
		window.draw(option);
	}

	for (const auto& polygon : polygons)
	{
		window.draw(polygon);
	}

	for (const auto& text : textParams)
	{
		window.draw(text);
	}
}


void SettingsMenu::detach()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		switch (getSelectedIndex())
		{
		case 0: adjustVolume(0, -1); break;
		case 1: adjustVolume(1, -1); break;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		switch (getSelectedIndex())
		{
		case 0: adjustVolume(0, 1); break;
		case 1: adjustVolume(1, 1); break;
		}
	}
}

void SettingsMenu::adjustVolume(int index, int delta)
{
	const int newValue = params[index] + delta;
	if (newValue < 0 || newValue > 100) return;

	params[index] = newValue;

	if (index == 0) 
	{
		Sounds->setAllSoundsVolume(newValue);
	}
	else 
	{
		Sounds->setAllMusicVolume(newValue);
	}

	textParams[index].setString(std::to_string(newValue));

	const float baseX = static_cast<float>(WIDTH) - MENU_ITEM_X_OFFSET * 1.5f;
	const float yPosition = static_cast<float>(HEIGHT) / MENU_ITEM_Y_START + index * MENU_ITEM_Y_OFFSET + 10;
	float xPosition = baseX - 65;

	if (newValue == 100) {
		xPosition = baseX - 75;
	}
	else if (newValue < 10) {
		xPosition += 15;
	}

	textParams[index].setPosition({ xPosition, yPosition });
}

gameState SettingsMenu::handleInput(sf::RenderWindow& window)
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
			if (getSelectedIndex() == 2)
			{
				Sounds->playSound("confirm");
				_Thrd_sleep_for(100);
				return gameState::Back;
			}

		}
		else
			detach();
	}
}