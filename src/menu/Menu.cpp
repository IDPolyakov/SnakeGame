#include "../../include/menu/Menu.h"

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
	constexpr float SOUND_VOLUME = 100.f;
}

Menu::Menu(float width, float height, const sf::Font& font, const sf::Texture& back)
	: 
	settings(width, height, font, back), 
	title(font),
	Background(back)
{
	initializeMenuItems(width, height, font);
	initializeSounds();
	initializeTitle(width, height);
}

Menu::~Menu() = default;

void Menu::initializeMenuItems(float width, float height, const sf::Font& font)
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
		text.setPosition({ xPosition, yPosition});
		menuItems.push_back(text);
	}
}

void Menu::initializeSounds()
{
	confirmSoundBuffer = std::make_unique<sf::SoundBuffer>("./resources/confirm.mp3");
	confirmSound = std::make_unique<sf::Sound>(*confirmSoundBuffer);
	confirmSound->setVolume(SOUND_VOLUME);

	choiceSoundBuffer = std::make_unique<sf::SoundBuffer>("./resources/choice.mp3");
	choiceSound = std::make_unique<sf::Sound>(*choiceSoundBuffer);
	choiceSound->setVolume(SOUND_VOLUME);
}

void Menu::initializeTitle(float width, float height)
{
	title.setString("Snake Game");
	title.setCharacterSize(TITLE_CHAR_SIZE);
	title.setFillColor(TITLE_COLOR);
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);

	const float xPosition = static_cast<float>(width) / 2.0f - TITLE_X_OFFSET;
	const float yPosition = static_cast<float>(height) / MENU_ITEM_Y_START - TITLE_Y_OFFSET;
	title.setPosition({ xPosition, yPosition });
}
void Menu::draw(sf::RenderWindow& window)
{
	window.draw(Background);
	window.draw(title);

	updateMenuItemsAnimation();

	float time = static_cast<float>(clock.getElapsedTime().asMilliseconds());
	float scale = 1.f + 0.05f * sin(time * 0.005f);
	for (const auto& item : menuItems)
		window.draw(item);
}

void Menu::drawSettings(sf::RenderWindow& window)
{
	settings.draw(window);
}

void Menu::updateMenuItemsAnimation()
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

void Menu::moveSelection(size_t direction)
{
	const size_t newIndex = selectedIndex + direction;

	if (newIndex >= 0 && newIndex < menuItems.size())
	{
		playChoiceSound();
		updateSelectedItem(selectedIndex, false);
		selectedIndex = newIndex;
		updateSelectedItem(selectedIndex, true);
		clock.restart();
	}
}

void Menu::updateSelectedItem(size_t index, bool isSelected)
{
	menuItems[index].setFillColor(isSelected ? SELECTED_COLOR : UNSELECTED_COLOR);
	menuItems[index].setCharacterSize(isSelected ? SELECTED_CHAR_SIZE : UNSELECTED_CHAR_SIZE);
}

void Menu::moveUp()
{
	moveSelection(-1);
}

void Menu::moveDown()
{
	moveSelection(1);
}

size_t Menu::getSelectedIndex() const
{
	return selectedIndex;
}

void Menu::playConfirmSound()
{
	confirmSound->play();
}

void Menu::playChoiceSound()
{
	choiceSound->play();
}