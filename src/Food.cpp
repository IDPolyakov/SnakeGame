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
	auto dice_x = bind(uniform_int_distribution<ll>(0, WIDTH / CELL - 1), rnd);
	auto dice_y = bind(uniform_int_distribution<ll>(0, HEIGHT / CELL - 1), rnd);

	while (true)
	{
		x = dice_x();
		y = dice_y();
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