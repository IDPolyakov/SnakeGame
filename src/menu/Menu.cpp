#include "../../include/menu/Menu.h";

Menu::Menu(ld width, ld height, const Font& font, const Texture& back) : title(font), Background(back)
{
	vector<string> items = {
		"Play",
		"Settings",
		"Exit"
	};
	selectedIndex = 0;
	for (ll i = 0; i < items.size(); i++)
	{
		Text text(font, items[i]);
		text.setFillColor(i == selectedIndex ? Color::Yellow : Color(200, 200, 200));
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2);
		text.setPosition({ float(width / 2.f - 60), float(height / 4.f + i * 90) });
		text.setCharacterSize(i == selectedIndex ? 46 : 40);
		menuItems.pb(text);
	}

	confirmSound.openFromFile("./resources/confirm.mp3");
	confirmSound.setVolume(100);

	choiceSound.openFromFile("./resources/choice.mp3");
	choiceSound.setVolume(100);

	title.setFont(font);
	title.setString("Snake Game");
	title.setCharacterSize(60);
	title.setFillColor(Color(255, 0, 0));
	title.setStyle(Text::Bold | Text::Underlined);
	title.setPosition({ float(width / 2.f - 180), float(height / 4.f - 150) });
}
void Menu::draw(RenderWindow& window)
{
	window.draw(Background);
	window.draw(title);


	float time = static_cast<float>(clock.getElapsedTime().asMilliseconds());
	float scale = 1.f + 0.05f * sin(time * 0.005f);
	for (ll i = 0; i < menuItems.size(); i++)
	{
		if (i == selectedIndex)
			menuItems[i].setScale({ scale, scale });
		else
			menuItems[i].setScale({ 1.f, 1.f });
		window.draw(menuItems[i]);
	}
}
void Menu::moveUp()
{
	if (selectedIndex > 0)
	{
		choiceSound.play();
		menuItems[selectedIndex].setFillColor(Color::White);
		menuItems[selectedIndex].setCharacterSize(40);
		selectedIndex--;
		menuItems[selectedIndex].setFillColor(Color::Yellow);
		menuItems[selectedIndex].setCharacterSize(46);
		clock.restart();
	}
}
void Menu::moveDown()
{
	if (selectedIndex < menuItems.size() - 1)
	{
		choiceSound.play();
		menuItems[selectedIndex].setFillColor(Color::White);
		menuItems[selectedIndex].setCharacterSize(40);
		selectedIndex++;
		menuItems[selectedIndex].setFillColor(Color::Yellow);
		menuItems[selectedIndex].setCharacterSize(46);
		clock.restart();
	}
}
ll Menu::getSelectedIndex() const
{
	return selectedIndex;
}
void Menu::playConfirmSound()
{
	confirmSound.play();
}