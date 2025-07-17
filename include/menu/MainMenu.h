#pragma once
#include "Core/IMenu.h"
#include "Core/IScene.h"

class MainMenu : public IMenu, public IScene
{
public:
	MainMenu(float width, float height, const sf::Font& font, const sf::Texture& back, SoundManager* Sounds_);
	
	gameState handleInput(sf::RenderWindow&) override;
	void render(sf::RenderWindow&) override;

	MainMenu(const MainMenu&) = delete;
	MainMenu& operator = (MainMenu&) = delete;

	~MainMenu() = default;
private:

	void initializeMenuItems(float width, float height, const sf::Font& font) override;
	void initializeTitle(float width, float height) override;
	void updateMenuItemsAnimation() override;
};