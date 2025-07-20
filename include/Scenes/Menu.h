#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Settings.h"

class Menu
{
public:
	Menu(float width, float height, const sf::Font& font, const sf::Texture& background);
	~Menu();

	void draw(sf::RenderWindow& window);
	void drawSettings(sf::RenderWindow& window);
	void moveUp();
	void moveDown();

	size_t getSelectedIndex() const;
	void playConfirmSound();
	void playChoiceSound();

	Menu(const Menu&) = delete;
	Menu& operator = (const Menu&) = delete;

private:
	void initializeMenuItems(float width, float height, const sf::Font& font);
	void initializeSounds();
	void initializeTitle(float width, float height);
	void updateMenuItemsAnimation();
	void moveSelection(size_t direction);
	void updateSelectedItem(size_t index, bool isSelected);

private:
	sf::Clock clock;
	sf::Text title;
	size_t selectedIndex = 0;
	std::vector<sf::Text> menuItems;

	const sf::Sprite Background;

	Settings settings;

	std::unique_ptr<sf::SoundBuffer> choiceSoundBuffer;
	std::unique_ptr<sf::SoundBuffer> confirmSoundBuffer;
	std::unique_ptr<sf::Sound> choiceSound;
	std::unique_ptr<sf::Sound> confirmSound;
};