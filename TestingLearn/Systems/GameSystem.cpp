#include "GameSystem.h"

pong::GameSystem::GameSystem(sf::RenderWindow* window) : onBallScoreEvSubs(nullptr)
{
	// Set window reference.
	this->window = window;

	// Set initial status.
	status = GameStatus();
}

pong::GameSystem::~GameSystem()
{
	// Unsubscribe events.
	onBallScoreEvSubs->Unsubscribe(onBallScoreFunc);

	playerOne = nullptr;
	playerTwo = nullptr;
	ball = nullptr;
	scoreP1 = nullptr;
	scoreP2 = nullptr;
}

pong::GameSystem::GameSystem(GameSystem const& arg) : onBallScoreEvSubs(nullptr)
{
	// Copy value.
	window = arg.window;

	// Set initial status.
	status = GameStatus();
}

void pong::GameSystem::operator=(GameSystem const& arg)
{
	// Copy value.
	window = arg.window;

	// Set initial status.
	status = arg.status;
}

void pong::GameSystem::initGame()
{
	// Get window size.
	sf::Vector2f windowSize = getWindowSize();

	// Create player 1.
	playerOne = createPaddle(sf::Vector2f(windowSize.x / 8.f,
		windowSize.y / 2.f), sf::Keyboard::Key::W, sf::Keyboard::Key::S, false);

	// Create player 2.
	playerTwo = createPaddle(sf::Vector2f(windowSize.x * 7.f / 8.f,
		windowSize.y / 2.f), sf::Keyboard::Key::Up, sf::Keyboard::Key::Down, true);

	// Create score for each players.
	scoreP1 = createScore(sf::Vector2f(getWindowSize().x / 4.f, 32.f), "Minecraft.ttf");
	scoreP2 = createScore(sf::Vector2f(getWindowSize().x * 3.f / 4.f, 32.f), "Minecraft.ttf");
}

void pong::GameSystem::startGame()
{
	// Reset countdown timer.
	tempBallRunIn = ballRunIn;

	// Set status.
	status.isStarting = true;
}

void pong::GameSystem::resetGame()
{
	// Set status.
	status.isRunning = false;

	// Reset ball position to the middle.
	float ballDiameter = ball->getDiameter();
	ball->setPosition((getWindowSize() - sf::Vector2f(ballDiameter, ballDiameter)) / 2.f);

	// Start the game immediately.
	startGame();
}

void pong::GameSystem::pauseGame()
{
	// Set status.
	status.isRunning = false;
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

pong::Score* pong::GameSystem::createScore(sf::Vector2f placement, std::string fontFile)
{
	pong::Score* score = new pong::Score(window, fontFile);
	score->setPosition(placement - (score->getBoundSize() / 2.f));
	pong::UIContainer::addRenderUI(score->getObjectID(), score);
	return score;
}

bool pong::GameSystem::isRoundCountdown()
{
	// Check countdown.
	if (tempBallRunIn > 0.f) {
		// Ticking a counter.
		tempBallRunIn -= pong::Time::getFixedDelta();

		// Release the ball if finish countdown.
		if (tempBallRunIn <= 0.f) {
			// Create a ball and set random direction, if already exists then set all initial info.
			if (!ball) {
				// Create ball instance.
				ball = pong::GameSystem::createBall(getWindowSize() / 2.f);

				// Create events.
				onBallScoreFunc = [this](const OnBallScoreEventArgs& arg) {
					// Receive score.
					if (arg.leftGoal) addP2Score(1);
					if (arg.rightGoal) addP1Score(1);

					// Reset the game system.
					this->resetGame();
				};

				// Subscribe events.
				onBallScoreEvSubs = ball->createOnBallScoreEvSubs();
				onBallScoreEvSubs->Subscribe(onBallScoreFunc);
			}

			// Set ball speed and velocity.
			ball->setSpeed(initialBallSpeed);
			ball->setVelocity(ball->getRandomDir());

			// Set status.
			status.isRunning = true;
			status.isStarting = false;
		}
		return true;
	}

	return false;
}

bool pong::GameSystem::isRoundRunning()
{
	return status.isRunning;
}

void pong::GameSystem::addP1Score(int a)
{
	scoreP1->setScore(scoreP1->getScore() + a);
}

void pong::GameSystem::addP2Score(int a)
{
	scoreP2->setScore(scoreP2->getScore() + a);
}
