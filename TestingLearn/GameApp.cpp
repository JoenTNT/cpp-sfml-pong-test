#include "GameApp.h"

//float changeBackgroundElapse = 1.f;

//void backgroundElapse(sf::Color* elapsedColor, sf::Color* nextColor, float percent) {
//	// Calculate elapsed color.
//	elapsedColor -> r = std::abs(windowColor.r + (nextColor -> r - windowColor.r) * percent);
//	elapsedColor -> g = std::abs(windowColor.g + (nextColor -> g - windowColor.g) * percent);
//	elapsedColor -> b = std::abs(windowColor.b + (nextColor -> b - windowColor.b) * percent);
//}

pong::GameApp::GameApp()
{
	// Create main window.
	windowSize = sf::Vector2i(minWindowWidth, minWindowHeight);
	mainWindow = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "PONG!");

	// Create main background of main window
	windowColor = sf::Color(24, 56, 120); // Start with black.
	background = new sf::RectangleShape(static_cast<sf::Vector2f>(windowSize));
	background->setFillColor(windowColor);

	// Init in game time.
	pong::Time::init();

	// Instantiate runtime container.
	runtimeEntities = std::vector<Runtime*>();
}

pong::GameApp::~GameApp()
{
	delete mainWindow;
	delete background;
}

pong::GameApp& pong::GameApp::getInstance()
{
	// Create singleton instance.
	static pong::GameApp instance;
	return instance;
}

sf::Vector2i pong::GameApp::getWindowSize()
{
	return getInstance().windowSize;
}

bool pong::GameApp::isRunning()
{
	return isAppRunning;
}

void pong::GameApp::onAwake()
{
	// Add a new ball.
	pong::PongBall* mainBall = new pong::PongBall(mainWindow, 12.5f);
	runtimeEntities.push_back(mainBall);
	
	// Set initial position of the ball to the middle of the window.
	float ballRadius = mainBall->getRadius();
	mainBall->setPosition((static_cast<sf::Vector2f>(windowSize) / 2.f)
		- sf::Vector2f(ballRadius, ballRadius));

	// Temp: Set Ball Velocity on start.
	mainBall->getVelocity()->setDirection(sf::Vector2f(785.5f, 125.5f));

	//float tempSecBeforeChangeBackground = changeBackgroundElapse, lerpPercent;
	//sf::Color nextColor = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
	//sf::Color elapsedColor(0, 0, 0);

	// Call awake for all runtime object.
	for (Runtime* objPtr : runtimeEntities)
		objPtr->onAwake();
}

void pong::GameApp::onUpdate()
{
	// Check termination of the app.
	if (!mainWindow->isOpen())
		isAppRunning = false;

	// Update delta time.
	pong::Time::tick();

	// Clear old frame.
	mainWindow->clear();

	// Draw main background.
	mainWindow->draw(*background);

	// Handle events
	sf::Event ev;
	while (mainWindow->pollEvent(ev))
	{
		// Check event.
		switch (ev.type)
		{
			// Event window close button pressed.
			case sf::Event::Closed:
				// Close main window
				mainWindow->close();
				break;

			case sf::Event::Resized:
				// Locked window resize.
				windowSize = static_cast<sf::Vector2i>(mainWindow->getSize());
				if (windowSize.x < minWindowWidth || windowSize.x > minWindowWidth)
					windowSize.x = minWindowWidth;
				if (windowSize.y < minWindowHeight || windowSize.y > minWindowHeight)
					windowSize.y = minWindowHeight;

				// Resetting window and background size.
				mainWindow->setSize(static_cast<sf::Vector2u>(windowSize));
				sf::Vector2f fWindowSize = static_cast<sf::Vector2f>(windowSize);
				background->setSize(fWindowSize);

				// Resize view.
				mainWindow->setView(sf::View(sf::FloatRect(0.f, 0.f, fWindowSize.x, fWindowSize.y)));
				break;

			//case sf::Event::MouseMoved:
			//	tempSecBeforeChangeBackground -= deltaTime.asSeconds();
			//	lerpPercent = 1.f - tempSecBeforeChangeBackground / changeBackgroundElapse;
			//	if (lerpPercent < 0.f) lerpPercent = 0;

			//	backgroundElapse(&elapsedColor, &nextColor, lerpPercent);

			//	// Check restart elapse time.
			//	if (tempSecBeforeChangeBackground <= 0.f)
			//	{
			//		// Set main window color.
			//		windowColor = nextColor;

			//		// Restart elapse.
			//		tempSecBeforeChangeBackground = changeBackgroundElapse;

			//		// Next Random color.
			//		nextColor = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
			//	}
			//	break;
		}
	}

	//// Set background fill color.
	//mainWindowBackgroundFill.setFillColor(elapsedColor);

	// Draw all entities.
	updateEntityIndex = 0;
	entitySize = static_cast<int>(runtimeEntities.size());
	while (updateEntityIndex < entitySize) {

		// Check empty object.
		if (runtimeEntities[updateEntityIndex] == nullptr)
		{
			runtimeEntities.erase(runtimeEntities.begin() + updateEntityIndex);
			entitySize--;
			continue;
		}

		// Update an object.
		runtimeEntities[updateEntityIndex]->onUpdate();

		// Next entity.
		updateEntityIndex++;
	}

	// Draw new frame.
	mainWindow->display();
}

void pong::GameApp::onEnd()
{
	// Cleaning up the runtime entities when the app ended.
	for (Runtime* objPtr : runtimeEntities) {

		// Call end process for each runtime objects.
		if (objPtr != nullptr)
			objPtr->onEnd();

		// Delete all objects.
		delete objPtr;
	}

	// Clear vector.
	runtimeEntities.clear();
}
