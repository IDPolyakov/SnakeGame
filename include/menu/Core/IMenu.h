#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

namespace {
	constexpr float MENU_ITEM_X_OFFSET = 60.0f;
	constexpr float MENU_ITEM_Y_OFFSET = 90.0f;
	constexpr float MENU_ITEM_Y_START = 4.0f;
	constexpr float TITLE_X_OFFSET = 180.0f;
	constexpr float TITLE_Y_OFFSET = 150.0f;

	const sf::Color SELECTED_COLOR = sf::Color::Yellow;
	const sf::Color UNSELECTED_COLOR = sf::Color(200, 200, 200);
	const sf::Color TITLE_COLOR = sf::Color(255, 0, 0);
	const sf::Color OUTLINE_COLOR = sf::Color::Black;

	constexpr unsigned SELECTED_CHAR_SIZE = 46;
	constexpr unsigned UNSELECTED_CHAR_SIZE = 40;
	constexpr unsigned TITLE_CHAR_SIZE = 60;
	constexpr unsigned OUTLINE_THICKNESS = 2;

	constexpr float ANIMATION_SPEED = 0.005f;
	constexpr float ANIMATION_SCALE = 0.05f;
}

class IMenu
{
protected: 
	sf::Text title;
	size_t selectedIndex = 0;
	std::vector<sf::Text> menuItems;
	
	sf::Clock clock;

	const sf::Sprite background;

protected:
	virtual void initializeMenuItems(float width, float height, const sf::Font& font) = 0;
	virtual void initializeTitle(float width, float height) = 0;
	virtual void updateMenuItemsAnimation() = 0;
	void moveSelection(size_t direction);
	void updateSelectedItem(size_t index, bool isSelected);
	
public:
	IMenu(float width, float height, const sf::Font& font, const sf::Texture& back);
	
	void moveUp();
	void moveDown();
	size_t getSelectedIndex() const;
	
	IMenu(const IMenu&) = delete;
	IMenu& operator = (const IMenu&) = delete;

	virtual ~IMenu() = default;
};