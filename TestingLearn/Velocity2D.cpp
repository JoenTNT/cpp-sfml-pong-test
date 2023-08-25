#include "Velocity2D.h"

pong::Velocity2D::Velocity2D(Transform2D* transform)
{
	this->transform = transform;
}

pong::Velocity2D::~Velocity2D()
{
	// Release references.
	transform = nullptr;
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
	sf::Vector2f transformPos = transform->getPosition();

	// Calculate velocity after one frame.
	float deltaTime = pong::Time::getSecondsDelta();
	transformPos.x += direction.x * deltaTime;
	transformPos.y += direction.y * deltaTime;

	// Set updated position information.
	transform->setPosition(transformPos);
}

void pong::Velocity2D::onEnd()
{
}
