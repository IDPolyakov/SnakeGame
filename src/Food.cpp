#include "../include/Food.h"
#include "../include/Snake.h"

namespace {
	const Color FOOD_COLOR = Color::Red;
	constexpr float SOUND_VOLUME = 100.f;
}

Food::Food()
{
	initializeShape();
}

Food::Food(const deque<Segment>& snake)
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

void Food::respawn(const deque<Segment>& snake)
{
	static mt19937 rnd(random_device{}());
	uniform_int_distribution<ll> dice_x(0, WIDTH / CELL - 1);
	uniform_int_distribution<ll> dice_y(0, HEIGHT / CELL - 1);

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
void Food::draw(RenderWindow& window) 
{
	shape.setPosition({ float((x + 0.5f) * CELL), float((y + 0.5f) * CELL) });
	window.draw(shape);
}
void Food::loadEatSound()
{
	eatSoundBuffer = make_unique<SoundBuffer>("./resources/eat.mp3");
	eatSound = make_unique<Sound>(*eatSoundBuffer);
	eatSound->setVolume(SOUND_VOLUME);
}
void Food::playEatSound()
{
	eatSound->play();
}