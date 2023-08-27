#include "PongBall.h"

pong::PongBall::PongBall(sf::RenderWindow* window, float ballRadius) : GameObject2D(window)
{
	// Create shape.
	shape = sf::CircleShape(ballRadius);
	shape.setFillColor(sf::Color::White);

	// Add velocity instance.
	velocityHandler = new Velocity2D(this);
}

pong::PongBall::~PongBall()
{
	delete velocityHandler;
}

pong::PongBall::PongBall(pong::PongBall const& ballRef) : GameObject2D(ballRef)
{
	// Create shape.
	shape = sf::CircleShape(ballRef.shape);

	// Add velocity instance.
	velocityHandler = new Velocity2D(this);
}

pong::PongBall& pong::PongBall::operator=(pong::PongBall const& ballRef)
{
	// Assign information to parent class.
	pong::GameObject2D::operator=(ballRef);

	// Copy shape information.
	shape.setRadius(ballRef.shape.getRadius());

	// Assignment finish, return this object.
	return *this;
}

float pong::PongBall::getRadius()
{
	return shape.getRadius();
}

float pong::PongBall::getDiameter()
{
	return getRadius() * 2.f;
}

void pong::PongBall::setSpeed(float speed)
{
	moveSpeed = speed;
}

float pong::PongBall::getSpeed()
{
	return moveSpeed;
}

void pong::PongBall::setAccelerate(float accelerate)
{
	accelerateSpeed = accelerate;
}

float pong::PongBall::getAccelerate()
{
	return accelerateSpeed;
}

void pong::PongBall::bounceX()
{
	// Change velocity x by negating it.
	sf::Vector2f currentVel = velocityHandler->getDirection();
	currentVel.x = -currentVel.x;
	velocityHandler->setDirection(currentVel);
}

void pong::PongBall::bounceY()
{
	// Change velocity y by negating it.
	sf::Vector2f currentVel = velocityHandler->getDirection();
	currentVel.y = -currentVel.y;
	velocityHandler->setDirection(currentVel);
}

void pong::PongBall::onAwake()
{
}

void pong::PongBall::onUpdate()
{
	// Running velocity before assigning final position.
	velocityHandler->onUpdate();

	// Bounce and predict bounce when reach the edge of the window.
	sf::Vector2f currentPos = getPosition();
	float ballDiameter = getDiameter();
	sf::Vector2f maxBoundPos = currentPos + sf::Vector2f(ballDiameter, ballDiameter);
	sf::Vector2f currentVel = velocityHandler->getDirection();
	sf::Vector2f fWindowSize = getWindow()->getView().getSize();
	if (maxBoundPos.y > fWindowSize.y || currentPos.y < 0.f) {
		//std::cout << "Current Y Position = " << currentPos.y << std::endl;

		/* Fixed bounce */
		/*currentPos.y = currentPos.y < 0.f ? 1.f : fWindowSize.y - ballDiameter - 1.f;
		maxBoundPos.y = currentPos.y + ballDiameter;*/

		/* Realistic bounce */
		// Get positive value of shifted position.
		float shiftedValueY = currentPos.y < 0.f ? -currentPos.y : maxBoundPos.y - fWindowSize.y;
		currentPos.y = currentPos.y < 0.f ? shiftedValueY : fWindowSize.y - shiftedValueY - ballDiameter;

		// Bounce the pong ball.
		bounceY();
	}
	if (maxBoundPos.x > fWindowSize.x || currentPos.x < 0.f) {
		//std::cout << "Current X Position = " << currentPos.x << std::endl;

		/* Fixed bounce */
		/*currentPos.x = (currentPos.x < 0.f ? 1.f : fWindowSize.x - ballDiameter - 1.f);
		maxBoundPos.x = currentPos.x + ballDiameter;*/

		/* Realistic bounce */
		// Get positive value of shifted position.
		float shiftedValueX = currentPos.x < 0.f ? -currentPos.x : maxBoundPos.x - fWindowSize.x;
		currentPos.x = currentPos.x < 0.f ? shiftedValueX : fWindowSize.x - shiftedValueX - ballDiameter;

		// Bounce the pong ball.
		bounceX();
	}

	// Update changed position and velocity.
	setPosition(currentPos);

	// Set ball sprite position.
	shape.setPosition(currentPos);

	// Draw the ball.
	onWindowDraw(&shape);
}

void pong::PongBall::onEnd()
{
}
