#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Settings
{
public: 
	Settings(float width, float height, const sf::Font& font, const sf::Texture& back);

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void toggleCurrentOption();
	int getSelectedIndex() const;


private:
	std::vector<sf::Text> optionTexts;
	std::vector<std::string> labels = { "Difficulty", "Sound", "Back" };
	std::vector<std::string> values = { "Normal", "On", "" };
	
	int selectedIndex;
	const sf::Font& font;
	const sf::Sprite Background;

	void updateStyles();
};

