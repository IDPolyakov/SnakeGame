#pragma once
#include <bits/stdc++.h>
#include "Food.h"
#include <SFML/Graphics.hpp>
//❤//
using namespace std;
using namespace sf;

enum class Direction { Up, Down, Left, Right };

struct Segment
{
    size_t x;
    size_t y;
	Segment(size_t x, size_t y) : x(x), y(y) {}
};

class Snake
{
public:
    Snake();

    void handleInput();
    void update(Food& food, float& delay);
    void draw(RenderWindow& window, float alpha);
    bool checkCollision() const;
    size_t getScore() const;
    const deque<Segment>& getBody() const;
    void reset();

    Snake(const Snake&) = delete;
    Snake& operator=(const Snake&) = delete;
private:
    void moveHead();
    void checkFoodCollision(Food& food, float& delay);
    void drawHead(RenderWindow& window, const float x, const float y);
    void drawBodySegment(RenderWindow& window, const float x, const float y, bool isHead);

    deque<Segment> body;
    deque<Segment> prevBody;
    Direction direction;
};

