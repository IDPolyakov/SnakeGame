#pragma once
#include "BaseMenu.h"

class MainMenu : public BaseMenu
{
public:
	MainMenu(float width, float height, const sf::Font& font, const sf::Texture& back);
	
	void draw(sf::RenderWindow&) override;

	MainMenu(const MainMenu&) = delete;
	MainMenu& operator = (BaseMenu&) = delete;

	~MainMenu() = default;
private:
	void initializeMenuItems(float width, float height, const sf::Font& font) override;
	void initializeTitle(float width, float height) override;
	void updateMenuItemsAnimation() override;
};