#include "../include/Food.h"
#include "../include/Snake.h"
Food::Food() : x(0), y(0) {}

Food::Food(const deque<Segment>& snake)
{
	shape.setRadius(CELL / 2.f);
	shape.setFillColor(Color::Red);
	respawn(snake);
}
void Food::respawn(const deque<Segment>& snake)
{
	static mt19937 rnd(time(0));
	uniform_int_distribution<ll> dice_x(0, WIDTH / CELL - 1);
	uniform_int_distribution<ll> dice_y(0, HEIGHT / CELL - 1);

	while (true)
	{
		x = dice_x(rnd);
		y = dice_y(rnd);
		bool onSnake = false;
		for (const auto& s : snake)
			if (s.x == x && s.y == y)
				onSnake = true;
		if (!onSnake) break;
	}
}
void Food::draw(RenderWindow& window) 
{
	shape.setPosition({ float(x * CELL), float(y * CELL) });
	window.draw(shape);
}