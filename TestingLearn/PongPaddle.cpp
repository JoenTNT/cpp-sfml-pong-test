#include "PongPaddle.h"

pong::PongPaddle::PongPaddle(sf::RenderWindow* window, sf::Vector2f paddleSize) : GameObject2D(window)
{
	//// Create velocity object.
	velocityHandler = new pong::Velocity2D(this);
	shape.setFillColor(sf::Color::White);

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
	// Assaign information to parent class.
	pong::GameObject2D::operator=(paddleRef);

	// Assignment finish, return this object.
	return *this;
}

void pong::PongPaddle::setControlKeys(sf::Keyboard::Key up, sf::Keyboard::Key down)
{
	upKey = up;
	downKey = down;
}

void pong::PongPaddle::setMoveSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

float pong::PongPaddle::getMoveSpeed()
{
	return moveSpeed;
}

sf::Vector2f pong::PongPaddle::getSize()
{
	return shape.getSize();
}

float pong::PongPaddle::getWidth()
{
	return shape.getSize().x;
}

float pong::PongPaddle::getHeight()
{
	return shape.getSize().y;
}

void pong::PongPaddle::onAwake()
{
}

void pong::PongPaddle::onUpdate()
{
	// Check control key event.
	isUpKeyPressed = sf::Keyboard::isKeyPressed(upKey);
	isDownKeyPressed = sf::Keyboard::isKeyPressed(downKey);

	// Check both key not pressed or either both pressed.
	if ((isUpKeyPressed && isDownKeyPressed) || (!isUpKeyPressed && !isDownKeyPressed)) {
		// Paddle doesn't move.
		velocityHandler->setDirection(sf::Vector2f(0.f, 0.f));
	}
	else if (isUpKeyPressed) { // Up key pressed.
		// Paddle move up.
		velocityHandler->setDirection(sf::Vector2f(0.f, -moveSpeed));
	}
	else if (isDownKeyPressed) { // Down key pressed.
		// Paddle move down.
		velocityHandler->setDirection(sf::Vector2f(0.f, moveSpeed));
	}

	// Update velocity and run it.
	velocityHandler->onUpdate();

	// Set sprite position.
	shape.setPosition(getPosition());

	// Draw the paddle.
	onWindowDraw(&shape);
}

void pong::PongPaddle::onEnd()
{
}
