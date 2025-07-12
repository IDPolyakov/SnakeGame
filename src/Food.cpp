#include "../include/Food.h"
#include "../include/Snake.h"

namespace {
	const sf::Color FOOD_COLOR = sf::Color::Red;
	constexpr float SOUND_VOLUME = 100.f;
}

Food::Food()
{
	initializeShape();
}

Food::Food(const std::deque<Segment>& snake)
{
	initializeShape();
	respawn(snake);
}

Food::~Food() = default;

void Food::initializeShape()
{
	shape.setRadius(CELL / 2.f);
	shape.setFillColor(FOOD_COLOR);
	shape.setOrigin({ shape.getRadius(), shape.getRadius() });
}

void Food::respawn(const std::deque<Segment>& snake)
{
	static std::mt19937 rnd(std::random_device{}());
	std::uniform_int_distribution<ll> dice_x(0, WIDTH / CELL - 1);
	std::uniform_int_distribution<ll> dice_y(0, HEIGHT / CELL - 1);

	do
	{
		x = dice_x(rnd);
		y = dice_y(rnd);
	} while (!isPositionValid(x, y, snake));
}

bool Food::isPositionValid(size_t foodX, size_t foodY, const std::deque<Segment>& snake) const
{
	for (const auto& segment : snake) 
	{
		if (segment.x == foodX && segment.y == foodY)
			return false;
	}
	return true;
}
void Food::draw(sf::RenderWindow& window) 
{
	shape.setPosition({ float((x + 0.5f) * CELL), float((y + 0.5f) * CELL) });
	window.draw(shape);
}
void Food::loadEatSound()
{
	eatSoundBuffer = std::make_unique<sf::SoundBuffer>("./resources/eat.mp3");
	eatSound = std::make_unique<sf::Sound>(*eatSoundBuffer);
	eatSound->setVolume(SOUND_VOLUME);
}
void Food::playEatSound()
{
	eatSound->play();
}