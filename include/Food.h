#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
//❤//
using namespace std;
using namespace sf;

struct Segment;

class Food
{
public:
	Food();
	~Food();
	explicit Food(const deque<Segment>& snake);
	void respawn(const deque<Segment>& snake);
	void draw(RenderWindow& window);
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

	CircleShape shape;
	unique_ptr<SoundBuffer> eatSoundBuffer;
	unique_ptr<Sound> eatSound;
};

