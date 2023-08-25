#include "PongBall.h"

pong::PongBall::PongBall(sf::RenderWindow* window, float ballRadius) : Transform2D(window)
{
	// Create shape.
	shape = sf::CircleShape(ballRadius);

	// Add velocity instance.
	velocityHandler = new Velocity2D(this);
}

pong::PongBall::~PongBall()
{
	delete velocityHandler;
}

pong::PongBall::PongBall(pong::PongBall const& ballRef) : Transform2D(ballRef)
{
	// Create shape.
	shape = sf::CircleShape(ballRef.shape.getRadius());
}

pong::PongBall& pong::PongBall::operator=(pong::PongBall const& ballRef)
{
	// Assign information to parent class.
	Transform2D::operator=(ballRef);

	// Copy shape information.
	shape.setRadius(ballRef.shape.getRadius());

	// Assignment finish, return this object.
	return *this;
}

pong::Velocity2D* pong::PongBall::getVelocity()
{
	return velocityHandler;
}

float pong::PongBall::getRadius()
{
	return shape.getRadius();
}

float pong::PongBall::getDiameter()
{
	return getRadius() * 2.f;
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
	sf::Vector2f fWindowSize = static_cast<sf::Vector2f>(pong::GameApp::getWindowSize());
	if (maxBoundPos.y > fWindowSize.y || currentPos.y < 0.f) {

		/* Fixed bounce */
		/*currentPos.y = currentPos.y < 0.f ? 1.f : fWindowSize.y - ballDiameter - 1.f;
		maxBoundPos.y = currentPos.y + ballDiameter;*/

		/* More Realistic bounce */
		float shiftedValueY;
		while (maxBoundPos.y > fWindowSize.y) { // Out of max Window Size.

			// Get shifted value outside the window, targeting positive value.
			shiftedValueY = maxBoundPos.y - fWindowSize.y;

			// Check if the bound is 2 or more windows out, then reflect it.
			if (shiftedValueY > fWindowSize.y)
				shiftedValueY -= fWindowSize.y * (int)(shiftedValueY / fWindowSize.y);

			// Change position after the shift.
			currentPos.y = fWindowSize.y - (shiftedValueY + ballDiameter);
			maxBoundPos.y = currentPos.y + ballDiameter;
		}
		while (currentPos.y < 0.f) { // Out of min Window Size.

			// Get shifted value outside the window, targeting positive value.
			shiftedValueY = -currentPos.y;

			// Check if the bound is 2 or more windows out, then reflect it.
			if (shiftedValueY > fWindowSize.y)
				shiftedValueY -= fWindowSize.y * (int)(shiftedValueY / fWindowSize.y);

			// Change position after the shift.
			currentPos.y = shiftedValueY;
		}

		// Change velocity y by negating it.
		currentVel = sf::Vector2f(currentVel.x, -currentVel.y);
		std::cout << "Velocity Changed! Current Position = (" << currentPos.x << ", " << currentPos.y
			<< ")" << std::endl;
	}
	if (maxBoundPos.x > fWindowSize.x || currentPos.x < 0.f) {

		/* Fixed bounce */
		/*currentPos.x = currentPos.x < 0.f ? 1.f : fWindowSize.x - ballDiameter - 1.f;
		maxBoundPos.x = currentPos.x + ballDiameter;*/

		/* More Realistic bounce */
		float shiftedValueX;
		while (maxBoundPos.x > fWindowSize.x) { // Out of max Window Size.

			// Get shifted value outside the window, targeting positive value.
			shiftedValueX = maxBoundPos.x - fWindowSize.x;

			// Check if the bound is 2 or more windows out, then reflect it.
			if (shiftedValueX > fWindowSize.x)
				shiftedValueX -= fWindowSize.x * (int)(shiftedValueX / fWindowSize.x);

			// Change position after the shift.
			currentPos.x = fWindowSize.x - (shiftedValueX + ballDiameter);
			maxBoundPos.x = currentPos.x + ballDiameter;
		}
		while (currentPos.x < 0.f) { // Out of min Window Size.

			// Get shifted value outside the window, targeting positive value.
			shiftedValueX = -currentPos.x;

			// Check if the bound is 2 or more windows out, then reflect it.
			if (shiftedValueX > fWindowSize.x)
				shiftedValueX -= fWindowSize.x * (int)(shiftedValueX / fWindowSize.x);

			// Change position after the shift.
			currentPos.x = shiftedValueX;
		}

		// Change velocity y by negating it.
		currentVel = sf::Vector2f(-currentVel.x, currentVel.y);
		std::cout << "Velocity Changed! Current Position = (" << currentPos.x << ", " << currentPos.y
			<< ")" << std::endl;
	}

	// Update changed velocity.
	velocityHandler->setDirection(currentVel);

	// Set ball sprite position.
	shape.setPosition(currentPos);

	// Draw the ball.
	onWindowDraw(&shape);
}

void pong::PongBall::onEnd()
{
}
