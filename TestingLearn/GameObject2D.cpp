#include "GameObject2D.h"

sf::RenderWindow* pong::GameObject2D::getWindow()
{
	return window;
}

pong::GameObject2D::GameObject2D(sf::RenderWindow* window)
{
	// Assign window target reference.
	this->window = window;

	// Generate object ID.
	objectID = getRandomID();

	// Debuging.
	std::cout << "[DEBUG] Object generated with ID: " << objectID << std::endl;
}

pong::GameObject2D::~GameObject2D()
{
	// Remove reference.
	window = nullptr;
}

pong::GameObject2D::GameObject2D(GameObject2D const& objRef)
	: window(objRef.window)
	, position(objRef.position)
{
	// Generate object ID.
	objectID = getRandomID();
}

pong::GameObject2D& pong::GameObject2D::operator=(GameObject2D const& objRef)
{
	// Assign with same reference.
	window = objRef.window;

	// Copy information.
	position = sf::Vector2f::Vector2(objRef.position);

	// Assignment finish, return this object.
	return *this;
}

void pong::GameObject2D::setPosition(sf::Vector2f pos)
{
	position = pos;
}

void pong::GameObject2D::setPosition(float x, float y)
{
	position = sf::Vector2f(x, y);
}

sf::Vector2f pong::GameObject2D::getPosition()
{
	return position;
}

unsigned long pong::GameObject2D::getObjectID()
{
	return objectID;
}

void pong::GameObject2D::onWindowDraw(sf::Shape* shape)
{
	window->draw(*shape);
}

unsigned long pong::GameObject2D::getRandomID()
{
	// Create random device.
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<unsigned long> distrib(0UL,
		std::numeric_limits<unsigned long>::max());

	// Check if ID already exists.
	unsigned long tempID;
	do {
		tempID = distrib(gen);
	} while (pong::RuntimeContainer::isIDExists(tempID));

	// Return generated random ID.
	return tempID;
}