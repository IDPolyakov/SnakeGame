#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//❤//
using namespace std;
using namespace sf;

class Menu
{
public:
	Menu(float width, float height, const Font& font, const Texture& background);
	~Menu();

	void draw(RenderWindow& window);
	void moveUp();
	void moveDown();

	size_t getSelectedIndex() const;
	void playConfirmSound();
	void playChoiceSound();

	Menu(const Menu&) = delete;
	Menu& operator = (const Menu&) = delete;

private:
	void initializeMenuItems(float width, float height, const Font& font);
	void initializeSounds();
	void initializeTitle(float width, float height);
	void updateMenuItemsAnimation();
	void moveSelection(size_t direction);
	void updateSelectedItem(size_t index, bool isSelected);

private:
	Clock clock;
	Text title;
	size_t selectedIndex = 0;
	vector<Text> menuItems;
	Sprite Background;

	unique_ptr<SoundBuffer> choiceSoundBuffer;
	unique_ptr<SoundBuffer> confirmSoundBuffer;
	unique_ptr<Sound> choiceSound;
	unique_ptr<Sound> confirmSound;
};