#include "../../include/menu/BaseMenu.h"

BaseMenu::BaseMenu(float width, float height, const sf::Font& font, const sf::Texture& back)
	:
	title(font),
	background(back)
{}

void BaseMenu::moveSelection(size_t direction)
{
	const size_t newIndex = selectedIndex + direction;

	if (newIndex >= 0 && newIndex < menuItems.size())
	{
		//playChoiceSound();
		updateSelectedItem(selectedIndex, false);
		selectedIndex = newIndex;
		updateSelectedItem(selectedIndex, true);
		clock.restart();
	}
}

void BaseMenu::updateSelectedItem(size_t index, bool isSelected)
{
	menuItems[index].setFillColor(isSelected ? SELECTED_COLOR : UNSELECTED_COLOR);
	menuItems[index].setCharacterSize(isSelected ? SELECTED_CHAR_SIZE : UNSELECTED_CHAR_SIZE);
}

void BaseMenu::moveUp()
{
	moveSelection(-1);
}

void BaseMenu::moveDown()
{
	moveSelection(1);
}

size_t BaseMenu::getSelectedIndex() const
{
	return selectedIndex;
}