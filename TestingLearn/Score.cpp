#include "Score.h"

pong::Score::Score(sf::RenderWindow* window, std::string fontFile) : GameObject2D(window)
{
	// Get font file.
	if (!font.loadFromFile("Minecraft.ttf"))
		throw std::runtime_error("[ERROR] Target font not found!");

	// Create text.
	text = new sf::Text("0", font, 36u);
	text->setFillColor(sf::Color::White);
}

pong::Score::~Score()
{
	delete text;
}

pong::Score::Score(Score const& arg) : GameObject2D(arg)
{
	// Get font file.
	if (!font.loadFromFile("Minecraft.ttf"))
		throw std::runtime_error("[ERROR] Target font not found!");

	// Create text.
	text = new sf::Text("0", font, 36u);
	text->setFillColor(sf::Color::White);
}

pong::Score& pong::Score::operator=(Score const& arg)
{
	// Assign information to parent class.
	pong::GameObject2D::operator=(arg);

	// Copy font file.
	font = arg.font;

	// Create text.
	text->setString(arg.text->getString());
	text->setFont(arg.font);
	text->setCharacterSize(arg.text->getCharacterSize());
	text->setFillColor(arg.text->getFillColor());

	// Make it the same value.
	value = arg.value;

	// Assignment finish, return this object.
	return *this;
}

void pong::Score::render()
{
	// Set UI position.
	text->setPosition(getPosition());

	// Render text.
	onWindowDraw(text);
}

sf::Vector2f pong::Score::getBoundSize()
{
	return text->getLocalBounds().getSize();
}

void pong::Score::setScore(int value)
{
	// Set value.
	this->value = value;

	// Change text value.
	text->setString(std::to_string(value));
}

int pong::Score::getScore()
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
