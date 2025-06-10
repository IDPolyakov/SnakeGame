#include "../include/Snake.h"

Snake::Snake()
{
	ld startX = WIDTH / (2 * CELL);
	ld startY = HEIGHT / (2 * CELL);
	body.emplace_back(startX, startY);
	prevBody = body;
	dir = Direction::Right;
}

void Snake::handleInput()
{
	if ((Keyboard::isKeyPressed(Keyboard::Key::Up) || Keyboard::isKeyPressed(Keyboard::Key::W)) && dir != Direction::Down)
		dir = Direction::Up;
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Down) || Keyboard::isKeyPressed(Keyboard::Key::S)) && dir != Direction::Up)
		dir = Direction::Down;
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A)) && dir != Direction::Right)
		dir = Direction::Left;
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D)) && dir != Direction::Left)
		dir = Direction::Right;
}
void Snake::update(Food& food, ld& delay)
{
	prevBody = body;
	Segment head = body.front();
	switch (dir)
	{
	case Direction::Up:
		head.y -= 1; break;
	case Direction::Down:
		head.y += 1; break;
	case Direction::Left:
		head.x -= 1; break;
	case Direction::Right:
		head.x += 1; break;
	}
	body.push_front(head);
	if (head.x == food.x && head.y == food.y)
	{
		food.playEatSound();
		food.respawn(body);
		delay *= 0.98;
	}
	else
		body.pop_back();
}
bool Snake::checkCollision()
{
	auto head = body.front();
	if (head.x < 0 || head.x >= WIDTH / CELL || head.y < 0 || head.y >= HEIGHT / CELL)
		return true;
	for (ll i = 1; i < body.size(); i++)
		if (body[i].x == head.x && body[i].y == head.y)
			return true;
	return false;
}
ll Snake::getScore() const
{
	return body.size() - 1;
}
const deque<Segment>& Snake::getBody() const
{
	return body;
}
void Snake::draw(RenderWindow& window, ld alpha)
{
	RectangleShape rect(Vector2f(CELL, CELL));
	
	for (ll i = 0; i < body.size(); i++)
	{
		ld px = (i < prevBody.size()) ? prevBody[i].x : body[i].x;
		ld py = (i < prevBody.size()) ? prevBody[i].y : body[i].y;
		ld cx = body[i].x;
		ld cy = body[i].y;

		ld interpX = (1 - alpha) * px + alpha * cx;
		ld interpY = (1 - alpha) * py + alpha * cy;

		rect.setPosition(Vector2f(interpX * CELL, interpY * CELL));
		rect.setFillColor(i == 0 ? Color(0, 100, 0) : Color::Green);
		window.draw(rect);

		if (i == 0)
		{

			CircleShape eye(2);
			eye.setFillColor(Color::White);
			eye.setPosition(Vector2f(interpX * CELL + 4, interpY * CELL + 4));
			window.draw(eye);
			eye.setPosition(Vector2f(interpX * CELL + 12, interpY * CELL + 4));
			window.draw(eye);
		}
	}
}