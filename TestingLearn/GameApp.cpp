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
	// Create game system as mandatory.
	sf::Vector2i windowSize = sf::Vector2i(minWindowWidth, minWindowHeight);
	mainWindow = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "PONG!");
	gameSystem = new pong::GameSystem(mainWindow);
	mainWindow->setFramerateLimit(60);
	mainWindow->setVerticalSyncEnabled(true);

	// Create main background of main window
	windowColor = sf::Color(0, 0, 0); // Start with black.
	background = new sf::RectangleShape(static_cast<sf::Vector2f>(windowSize));
	background->setFillColor(windowColor);
}

pong::GameApp::~GameApp()
{
	delete mainWindow;
	delete gameSystem;
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
	return static_cast<sf::Vector2i>(getInstance().mainWindow->getView().getSize());
}

bool pong::GameApp::isRunning()
{
	return isAppRunning;
}

void pong::GameApp::onAwake()
{
	// Initialize objects from system.
	gameSystem->initGame();

	// Run awake method.
	pong::RuntimeContainer::awake();

	//float tempSecBeforeChangeBackground = changeBackgroundElapse, lerpPercent;
	//sf::Color nextColor = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
	//sf::Color elapsedColor(0, 0, 0);
}

sf::Vector2f fWindowSize;
float ratio;

void pong::GameApp::onUpdate()
{
	// Check termination of the app.
	if (!mainWindow->isOpen()) isAppRunning = false;

	// Check if game app is currently focused, if not then do not run the update.
	if (!mainWindow->hasFocus()) return;

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
				sf::Vector2i windowSize = getWindowSize();
				if (windowSize.x < minWindowWidth) windowSize.x = minWindowWidth;
				if (windowSize.y < minWindowHeight) windowSize.y = minWindowHeight;

				// Calculate sync ratio.
				ratio = (float)minWindowWidth / (float)minWindowHeight;
				windowSize.y = (int)((float)windowSize.x / ratio);

				// Resetting window and background size.
				mainWindow->setSize(static_cast<sf::Vector2u>(windowSize));
				fWindowSize = static_cast<sf::Vector2f>(windowSize);
				background->setSize(fWindowSize);
				//std::cout << "Resizing... (" << windowSize.x << ", " << windowSize.y << ")" << std::endl;

				// Resize view.
				//mainWindow->setView(sf::View(sf::FloatRect(0.f, 0.f, fWindowSize.x, fWindowSize.y)));
				windowSize = static_cast<sf::Vector2i>(mainWindow->getView().getSize());
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
		//std::cout << "Running Event" << std::endl;
	}

	//// Set background fill color.
	//mainWindowBackgroundFill.setFillColor(elapsedColor);

	// Runtime update all runtime.
	pong::RuntimeContainer::update();
	mainWindow->draw(scoreText);

	// Draw new frame.
	mainWindow->display();
}

void pong::GameApp::onEnd()
{
	pong::RuntimeContainer::end();
}
