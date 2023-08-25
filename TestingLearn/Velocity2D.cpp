#include "Velocity2D.h"

pong::Velocity2D::Velocity2D(GameObject2D* gameObject)
{
	this->gameObject = gameObject;
}

pong::Velocity2D::~Velocity2D()
{
	// Release references.
	gameObject = nullptr;
}

void pong::Velocity2D::setDirection(sf::Vector2f dir)
{
	direction = dir;
}

void pong::Velocity2D::setDirection(float x, float y)
{
	direction = sf::Vector2f(x, y);
}

sf::Vector2f pong::Velocity2D::getDirection()
{
	return direction;
}

void pong::Velocity2D::onAwake()
{
}

void pong::Velocity2D::onUpdate()
{
	// Get current position information.
	sf::Vector2f transformPos = gameObject->getPosition();

	// Calculate velocity after one frame.
	float deltaTime = pong::Time::getSecondsDelta();
	transformPos.x += direction.x * deltaTime;
	transformPos.y += direction.y * deltaTime;

	// Set updated position information.
	gameObject->setPosition(transformPos);
}

void pong::Velocity2D::onEnd()
{
}
