#include "../include/Snake.h"

namespace {
	const sf::Color HEAD_COLOR(0, 100, 0);
	const sf::Color BODY_COLOR = sf::Color::Green;
	const sf::Color EYE_COLOR = sf::Color::White;
	const float SPEED_INCREASE_FACTOR = 0.98f;
	const float EYE_RADIUS = CELL / 10.f;
	const float EYE_OFFSET_X1 = CELL / 5.f;
	const float EYE_OFFSET_X2 = CELL / 1.66f;
	const float EYE_OFFSET_Y = CELL / 5.f;
}


Snake::Snake()
{
	reset();
}

void Snake::handleInput()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) && direction != Direction::Down)
		direction = Direction::Up;
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && direction != Direction::Up)
		direction = Direction::Down;
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) && direction != Direction::Right)
		direction = Direction::Left;
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && direction != Direction::Left)
		direction = Direction::Right;
}

void Snake::update(Food& food, float& delay)
{
	prevBody = body;

	moveHead();
	checkFoodCollision(food, delay);
}

void Snake::moveHead()
{
	Segment head = body.front();
	switch (direction)
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
}

void Snake::checkFoodCollision(Food& food, float& delay)
{
	const auto& head = body.front();
	if (head.x == food.getX() && head.y == food.getY())
	{
		food.playEatSound();
		food.respawn(body);
		delay *= SPEED_INCREASE_FACTOR;
	}
	else
		body.pop_back();
}
bool Snake::checkCollision() const
{
	/*auto head = body.front();
	if (head.x < 0 || head.x >= WIDTH / CELL || head.y < 0 || head.y >= HEIGHT / CELL)
		return true;
	for (ll i = 1; i < body.size(); i++)
		if (body[i].x == head.x && body[i].y == head.y)
			return true;
	return false;*/

	const auto& head = body.front();
	if (head.x >= WIDTH / CELL || head.y >= HEIGHT / CELL)
		return true;

	return any_of(body.begin() + 1, body.end(),
		[&head](const auto& segment) {
			return segment.x == head.x && segment.y == head.y;
		});
}
size_t Snake::getScore() const
{
	return body.size() - 1;
}
const std::deque<Segment>& Snake::getBody() const
{
	return body;
}
void Snake::draw(sf::RenderWindow& window, float alpha)
{
	//RectangleShape rect(Vector2f(CELL, CELL));
	
	for (ll i = 0; i < body.size(); i++)
	{
		const float prevX = (i < prevBody.size()) ? prevBody[i].x : body[i].x;
		const float prevY = (i < prevBody.size()) ? prevBody[i].y : body[i].y;

		const float interpX = (1 - alpha) * prevX + alpha * body[i].x;
		const float interpY = (1 - alpha) * prevY + alpha * body[i].y;

		if (i == 0)
			drawHead(window, interpX, interpY);
		else
			drawBodySegment(window, interpX, interpY, false);
	}
}

void Snake::drawHead(sf::RenderWindow& window, const float x, const float y) 
{
	drawBodySegment(window, x, y, true);

	sf::CircleShape eye(EYE_RADIUS);
	eye.setFillColor(EYE_COLOR);

	const float pixelX = x * CELL;
	const float pixelY = y * CELL;

	eye.setPosition({ pixelX + EYE_OFFSET_X1, pixelY + EYE_OFFSET_Y });
	window.draw(eye);

	eye.setPosition({ pixelX + EYE_OFFSET_X2, pixelY + EYE_OFFSET_Y });
	window.draw(eye);
}

void Snake::drawBodySegment(sf::RenderWindow& window, const float x, const float y, bool isHead)
{
	sf::RectangleShape segment(sf::Vector2f(CELL, CELL));
	segment.setPosition({ x * CELL, y * CELL });
	segment.setFillColor(isHead ? HEAD_COLOR : BODY_COLOR);
	window.draw(segment);
}

void Snake::reset()
{
	const size_t startX = WIDTH / (2 * CELL);
	const size_t startY = HEIGHT / (2 * CELL);
	body.emplace_back(startX, startY);
	prevBody = body;
	direction = Direction::Right;
}