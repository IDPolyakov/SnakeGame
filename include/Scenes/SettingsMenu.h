#pragma once
#include <bits/stdc++.h>
#include "../Core/IMenu.h"
#include "../Core/IScene.h"


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
	const std::vector<std::string> menuItemLabels = {
		"Sounds",
		"Music",
		"Back"
	};

	std::vector<sf::ConvexShape> polygons;
	std::vector<int> params = { 100, 100};
	std::vector<sf::Text> textParams;

	void detach();
	void adjustVolume(int index, int delta);

	void initializeParams(float width, float height, const sf::Font& font);
	void initializePolygons(float width, float height);
	void initializeMenuItems(float width, float height, const sf::Font& font) override;
	void initializeTitle(float width, float height) override;
	void updateMenuItemsAnimation() override;
};

