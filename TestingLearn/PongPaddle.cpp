#include "PongPaddle.h"

void pong::PongPaddle::checkBall(PongBall* ball)
{
	// Get paddle and ball position.
	sf::Vector2f ballPos = ball->getPosition();
	sf::Vector2f paddlePos = getPosition();
	sf::Vector2f paddleSize = getSize();
	unsigned long ballID = ball->getObjectID();
	float ballDiameter = ball->getDiameter();

	// Check left face of paddle hit. (Ball hit to the right)
	float ballRightBound = ballPos.x + ballDiameter;
	if (bounceLeft && ballRightBound > paddlePos.x && ballPos.x < paddlePos.x) {
		// Check if the ball is still inside the paddle, then ignore process.
		if (ballInsidePaddle.find(ballID) != ballInsidePaddle.end())
			return;

		// Check on Y hit.
		if (isBallOnYHit(ballPos, paddlePos, ballDiameter, paddleSize.y))
		{
			// Bounce the ball and accelerate it.
			ball->bounceX();
			ball->accelerate();

			// Ball status inside the paddle must be ignored on the next frame.
			ballInsidePaddle.insert(ballID);
		}
		return;
	}

	// Check right face of paddle hit. (Ball hit to the left)
	float rightBound = paddlePos.x + paddleSize.x;
	if (bounceRight && ballPos.x < rightBound && ballRightBound > rightBound) {
		// Check if the ball is still inside the paddle, then ignore process.
		if (ballInsidePaddle.find(ballID) != ballInsidePaddle.end())
			return;

		// Check on Y hit.
		if (isBallOnYHit(ballPos, paddlePos, ballDiameter, paddleSize.y))
		{
			// Bounce the ball and accelerate it.
			ball->bounceX();
			ball->accelerate();

			// Ball status inside the paddle must be ignored on the next frame.
			ballInsidePaddle.insert(ballID);
		}
		return;
	}

	// If not both above, try release ball from inside the paddle.
	if (ballInsidePaddle.find(ballID) != ballInsidePaddle.end())
		ballInsidePaddle.erase(ballID);
}

bool pong::PongPaddle::isBallOnYHit(sf::Vector2f ballPos, sf::Vector2f paddlePos, float ballDiameter,
	float paddleHeight)
{
	// Check if ball is under the paddle.
	if (ballPos.y > paddlePos.y + paddleHeight)
		return false;

	// Check if ball is above the paddle.
	if (ballPos.y + ballDiameter < paddlePos.y)
		return false;

	// Else then the ball hit the paddle.
	return true;
}

pong::PongPaddle::PongPaddle(sf::RenderWindow* window, sf::Vector2f paddleSize) : GameObject2D(window)
{
	// Create velocity object.
	velocityHandler = new pong::Velocity2D(this);
	shape.setFillColor(sf::Color::White);

	// Create paddle shape.
	shape = sf::RectangleShape(paddleSize);
	ballsOnMap = std::unordered_map<unsigned long, pong::PongBall*>();
	ballInsidePaddle = std::unordered_set<unsigned long>();

	// Create subscriber.
	onAddRuntimeEvSubs = RuntimeContainer::createOnAddRuntimeEvSubs();
}

pong::PongPaddle::PongPaddle(sf::RenderWindow* window, float sizeX, float sizeY) : GameObject2D(window)
{
	// Create velocity object.
	velocityHandler = new pong::Velocity2D(this);

	// Create paddle shape.
	shape = sf::RectangleShape(sf::Vector2f(sizeX, sizeY));

	// Create subscriber.
	onAddRuntimeEvSubs = RuntimeContainer::createOnAddRuntimeEvSubs();
}

pong::PongPaddle::~PongPaddle()
{
	delete velocityHandler;
	delete onAddRuntimeEvSubs;
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

void pong::PongPaddle::setBounceLeft()
{
	bounceLeft = true;
	bounceRight = false;
}

void pong::PongPaddle::setBounceRight()
{
	bounceLeft = false;
	bounceRight = true;
}

void pong::PongPaddle::onAwake()
{
	// Create a functions.
	onAddRuntimeFunc = [this](const OnAddRuntimeEventArgs& args) {
		PongBall* ball = dynamic_cast<PongBall*>(args.runtime);
		if (ball) {
			std::cout << "Found Ball!" << std::endl;
			ballsOnMap.emplace(std::make_pair(args.id, ball));
		}
	};

	// Subscribe events.
	onAddRuntimeEvSubs->Subscribe<OnAddRuntimeEventArgs>(onAddRuntimeFunc);
}

void pong::PongPaddle::onUpdate()
{
	// Check control key event.
	sf::Vector2f paddlePos = getPosition();
	float windowSizeY = getWindow()->getView().getSize().y;
	float paddleSizeY = getSize().y, velDir = velocityHandler->getDirection().y;
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

	// Check limit.
	if (!(paddlePos.y + paddleSizeY >= windowSizeY && velDir > 0.f)
		&& !(paddlePos.y <= 0.f && velDir < -0.f))
	{
		// Update velocity and run it.
		velocityHandler->onUpdate();
	}

	// Set sprite position.
	shape.setPosition(paddlePos);

	// Check if a ball hits the paddle.
	//RuntimeContainer::getRuntimeObjects(&ballsOnMap);
	for (auto& ball : ballsOnMap) checkBall(ball.second);

	// Draw the paddle.
	onWindowDraw(&shape);
}

void pong::PongPaddle::onEnd()
{
	// Unsubscribe events.
	//std::function<void(unsigned long, IRuntime*)> func;
	//func = std::bind(&listenOnAddRuntime, this, std::placeholders::_1, std::placeholders::_2);
	//pong::RuntimeContainer::unsubsOnAddRuntime(func);
	onAddRuntimeEvSubs->Unsubscribe<OnAddRuntimeEventArgs>(onAddRuntimeFunc);
}
