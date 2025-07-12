#include "../../include/menu/Settings.h"

Settings::Settings(float width, float height, const sf::Font& font, const sf::Texture& back) 
	:
	font(font), 
	Background(back)
{
	selectedIndex = 0;

	for (int i = 0; i < labels.size(); i++)
	{
		std::string textStr = labels[i];
		if (!values[i].empty())
		{
			textStr += ": " + values[i];
		}

		sf::Text text(font, textStr, 40);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2);
		text.setPosition({ float(width / 2.f - 120), float(height / 4.f + i * 90) });
		text.setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color(200, 200, 200));
		optionTexts.push_back(text);
	}
}

void Settings::draw(sf::RenderWindow& window)
{

	window.draw(Background);

	for (const auto& option : optionTexts)
	{
		window.draw(option);
	}
}

void Settings::moveUp()
{
	if (selectedIndex > 0)
	{
		selectedIndex--;
		updateStyles();
	}
}

void Settings::moveDown()
{
	if (selectedIndex < optionTexts.size() - 1)
	{
		selectedIndex++;
		updateStyles();
	}
}

void Settings::toggleCurrentOption()
{
	if (labels[selectedIndex] == "Difficulty")
	{
		values[selectedIndex] = (values[selectedIndex] == "Normal" ? "Hard" : "Normal");
	}
	else if (labels[selectedIndex] == "Sound")
	{
		values[selectedIndex] = (values[selectedIndex] == "On" ? "Off" : "On");
	}

	// Обновление текста
	std::string textStr = labels[selectedIndex] + ": " + values[selectedIndex];
	optionTexts[selectedIndex].setString(textStr);
}

int Settings::getSelectedIndex() const
{
	return selectedIndex;
}

void Settings::updateStyles()
{
	for (int i = 0; i < optionTexts.size(); i++)
	{
		optionTexts[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color(200, 200, 200));
	}
}