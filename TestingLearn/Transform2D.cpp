#include "Transform2D.h"

pong::Transform2D::Transform2D(sf::RenderWindow* window)
{
	this->window = window;
}

pong::Transform2D::~Transform2D()
{
	// Remove reference.
	window = nullptr;
}

pong::Transform2D::Transform2D(Transform2D const& objRef)
	: window(objRef.window)
	, position(objRef.position)
{
}

pong::Transform2D& pong::Transform2D::operator=(Transform2D const& objRef)
{
	// Assign with same reference.
	window = objRef.window;

	// Copy information.
	position = sf::Vector2f::Vector2(objRef.position);

	// Assignment finish, return this object.
	return *this;
}

void pong::Transform2D::setPosition(sf::Vector2f pos)
{
	position = pos;
}

void pong::Transform2D::setPosition(float x, float y)
{
	position = sf::Vector2f(x, y);
}

sf::Vector2f pong::Transform2D::getPosition()
{
	return position;
}

void pong::Transform2D::onWindowDraw(sf::Shape* shape)
{
	window->draw(*shape);
}
