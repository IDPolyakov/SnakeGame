#pragma once
#include <bits/stdc++.h>
#include "Core/IMenu.h"
#include "Core/IScene.h"


class SettingsMenu : public IMenu, public IScene
{
public:
	SettingsMenu(float width, float height, const sf::Font& font, const sf::Texture& back, SoundManager* Sounds_);

	void render(sf::RenderWindow&) override;
	gameState handleInput(sf::RenderWindow&) override;

	SettingsMenu(const SettingsMenu&) = delete;
	SettingsMenu& operator = (SettingsMenu&) = delete;

	~SettingsMenu() = default;
private:
	void initializeMenuItems(float width, float height, const sf::Font& font) override;
	void initializeTitle(float width, float height) override;
	void updateMenuItemsAnimation() override;
};

