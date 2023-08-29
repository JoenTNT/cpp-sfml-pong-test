#include "Score.h"

pong::Score::Score(sf::RenderWindow* window, std::string fontFile)
	: GameObject2D(window)
{
	// Get font 
	if (!font.loadFromFile("Minecraft.ttf"))
		throw std::runtime_error("[ERROR] Target font not found!");

	text = new sf::Text("0", font, 36u);
	text->setFillColor(sf::Color::White);
	text->setPosition(placement);
}

pong::Score::~Score()
{
	delete text;
}

pong::Score::Score(Score const& arg) : GameObject2D(arg.)
{
}

void pong::Score::operator=(Score const& arg)
{
}

void pong::Score::setScore(int value)
{
}

float pong::Score::getScore()
{
	return value;
}

bool pong::Score::operator>(Score const& comp)
{
	return this->value > comp.value;
}

bool pong::Score::operator<(Score const& comp)
{
	return this->value < comp.value;
}

bool pong::Score::operator>=(Score const& comp)
{
	return this->value >= comp.value;
}

bool pong::Score::operator<=(Score const& comp)
{
	return this->value <= comp.value;
}

bool pong::Score::operator==(Score const& comp)
{
	return this->value == comp.value;
}

bool pong::Score::operator!=(Score const& comp)
{
	return this->value != comp.value;
}
