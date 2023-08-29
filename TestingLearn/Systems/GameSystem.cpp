#include "GameSystem.h"

pong::GameSystem::GameSystem(sf::RenderWindow* window)
{
	this->window = window;
}

pong::GameSystem::~GameSystem() { }

pong::GameSystem::GameSystem(GameSystem const& arg)
{
	// Copy value.
	window = arg.window;
}

void pong::GameSystem::operator=(GameSystem const& arg)
{
	// Copy value.
	window = arg.window;
}

void pong::GameSystem::initGame()
{
	// Create a ball.
	sf::Vector2f windowSize = getWindowSize();
	pong::GameSystem::createBall(windowSize / 2.f);

	// Create player 1.
	pong::GameSystem::createPaddle(sf::Vector2f(windowSize.x / 8.f,
		windowSize.y / 2.f), sf::Keyboard::Key::W, sf::Keyboard::Key::S, false);

	// Create player 2.
	pong::GameSystem::createPaddle(sf::Vector2f(windowSize.x * 7.f / 8.f,
		windowSize.y / 2.f), sf::Keyboard::Key::Up, sf::Keyboard::Key::Down, true);

	// Create score for playr 1.
	pong::Score score = pong::Score(window, "Minecraft.ttf");
	sf::Vector2f((getWindowSize().x - score.getLocalBounds().width) / 2.f, 18.f)
}

void pong::GameSystem::startGame()
{
}

void pong::GameSystem::resetGame()
{
}

void pong::GameSystem::pauseGame()
{
}

sf::Vector2f pong::GameSystem::getWindowSize()
{
	return window->getView().getSize();
}

pong::PongBall* pong::GameSystem::createBall(sf::Vector2f centerWindow)
{
	// Create ball object.
	pong::PongBall* mainBall = new pong::PongBall(window, 12.5f);
	pong::RuntimeContainer::addRuntime(mainBall->getObjectID(), mainBall);

	// Set initial position of the ball to the middle of the window.
	float ballRadius = mainBall->getRadius();
	mainBall->setPosition(centerWindow - (sf::Vector2f(ballRadius, ballRadius) / 2.f));
	return mainBall;
}

pong::PongPaddle* pong::GameSystem::createPaddle(sf::Vector2f placement,
	sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, bool isLeftBounce)
{
	// Create pong paddle object.
	pong::PongPaddle* p = new pong::PongPaddle(window, sf::Vector2f(20.f, 60.f));
	pong::RuntimeContainer::addRuntime(p->getObjectID(), p);
	p->setPosition(placement.x - (p->getWidth() / 2.f), placement.y - (p->getHeight() / 2.f));
	p->setControlKeys(upKey, downKey);

	// Set paddle bounce.
	if (isLeftBounce) p->setBounceLeft();
	else p->setBounceRight();
	return p;
}

bool pong::GameSystem::isRoundRunning()
{
	return isRunning;
}
