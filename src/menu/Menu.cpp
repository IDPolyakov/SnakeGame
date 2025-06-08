#include "../../include/menu/Menu.h";

Menu::Menu(ld width, ld height, const Font& font)
{
	vector<string> items = {
		"Play",
		"Options",
		"Exit"
	};
	selectedIndex = 0;
	for (ll i = 0; i < items.size(); i++)
	{
		Text text(font, items[i], 40);
		text.setFillColor(i == 0 ? Color::Yellow : Color::White);
		text.setPosition({ float(width / 2.f - 50), float(height / 3.f + i * 60) });
		menuItems.pb(text);
	}
}
void Menu::draw(RenderWindow& window)
{
	for (const auto& it : menuItems)
		window.draw(it);
}
void Menu::moveUp()
{
	if (selectedIndex > 0)
	{
		menuItems[selectedIndex].setFillColor(Color::White);
		selectedIndex--;
		menuItems[selectedIndex].setFillColor(Color::Yellow);
	}
}
void Menu::moveDown()
{
	if (selectedIndex < menuItems.size() - 1)
	{
		menuItems[selectedIndex].setFillColor(Color::White);
		selectedIndex++;
		menuItems[selectedIndex].setFillColor(Color::Yellow);
	}
}
ll Menu::getSelectedIndex() const
{
	return selectedIndex;
}