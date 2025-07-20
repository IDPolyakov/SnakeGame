#include "../../include/Core/IMenu.h"

IMenu::IMenu(float width, float height, const sf::Font& font, const sf::Texture& back)
	:
	title(font),
	background(back)
{}

void IMenu::moveSelection(size_t direction)
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

void IMenu::updateSelectedItem(size_t index, bool isSelected)
{
	menuItems[index].setFillColor(isSelected ? SELECTED_COLOR : UNSELECTED_COLOR);
	menuItems[index].setCharacterSize(isSelected ? SELECTED_CHAR_SIZE : UNSELECTED_CHAR_SIZE);
}

void IMenu::moveUp()
{
	moveSelection(-1);
}

void IMenu::moveDown()
{
	moveSelection(1);
}

size_t IMenu::getSelectedIndex() const
{
	return selectedIndex;
}