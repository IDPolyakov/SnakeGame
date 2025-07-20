#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Constants.h"
#include "../Core/SoundManager.h"

struct Segment;

class Food
{
public:
	Food();
	~Food();
	explicit Food(const std::deque<Segment>& snake, SoundManager* Sounds_);
	void respawn(const std::deque<Segment>& snake);
	void draw(sf::RenderWindow& window);
	void loadEatSound();
	void playEatSound();

	Food(const Food&) = delete;
	Food& operator=(const Food&) = delete;

	size_t getX() const { return x; }
	size_t getY() const { return y; }
private:
	void initializeShape();
	bool isPositionValid(size_t foodX, size_t foodY, const std::deque<Segment>& snake) const;

	unsigned x = 0;
	unsigned y = 0;

	sf::CircleShape shape;
	SoundManager* sounds;
};

