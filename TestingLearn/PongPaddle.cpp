#include "PongPaddle.h"

pong::PongPaddle::PongPaddle(sf::RenderWindow* window, sf::Vector2f paddleSize) : GameObject2D(window)
{
	// Create velocity object.
	velocityHandler = new pong::Velocity2D(this);

	// Create paddle shape.
	shape = sf::RectangleShape(paddleSize);
}

pong::PongPaddle::PongPaddle(sf::RenderWindow* window, float sizeX, float sizeY) : GameObject2D(window)
{
	// Create velocity object.
	velocityHandler = new pong::Velocity2D(this);

	// Create paddle shape.
	shape = sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
}

pong::PongPaddle::~PongPaddle()
{
	delete velocityHandler;
}

pong::PongPaddle::PongPaddle(PongPaddle const& paddleRef) : GameObject2D(paddleRef)
{
	// Create velocity object.
	velocityHandler = new pong::Velocity2D(this);

	// Create paddle shape.
	shape = sf::RectangleShape(paddleRef.shape);
}

pong::PongPaddle& pong::PongPaddle::operator=(PongPaddle const& paddleRef)
{
	// Assign information to parent class.
	PongPaddle::operator=(paddleRef);

	// Assignment finish, return this object.
	return *this;
}

void pong::PongPaddle::onAwake()
{
}

void pong::PongPaddle::onUpdate()
{
}

void pong::PongPaddle::onEnd()
{
}
