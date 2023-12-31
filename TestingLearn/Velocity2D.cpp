#include "Velocity2D.h"

pong::Velocity2D::Velocity2D(GameObject2D* gameObject)
{
	// Assign game object reference.
	this->gameObject = gameObject;

	// Set initial direction.
	direction = sf::Vector2f(0.f, 0.f);
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

float pong::Velocity2D::getMagnitude()
{
	return std::sqrtf(direction.x * direction.x + direction.y * direction.y);
}

sf::Vector2f pong::Velocity2D::getNormalDir()
{
	return direction / getMagnitude();
}

void pong::Velocity2D::onAwake()
{
}

void pong::Velocity2D::onUpdate()
{
	// Get current position information.
	sf::Vector2f transformPos = gameObject->getPosition();

	// Calculate velocity after one frame.
	float deltaTime = pong::Time::getFixedDelta();
	transformPos.x += direction.x * deltaTime;
	transformPos.y += direction.y * deltaTime;

	// Set updated position information.
	gameObject->setPosition(transformPos);
}

void pong::Velocity2D::onEnd()
{
}
