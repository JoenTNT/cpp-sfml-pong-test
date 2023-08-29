#pragma once
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Score.h"
#include "../PongPaddle.h"

namespace pong
{
	class GameSystem final
	{
	private:
		sf::RenderWindow* window;

		float ballRunIn = 3.f; // In Seconds.
		bool isRunning = false;

	public:
		GameSystem(sf::RenderWindow* window);

		~GameSystem();
		GameSystem(GameSystem const& arg);
		void operator=(GameSystem const& arg);

		void initGame();
		void startGame();
		void resetGame();
		void pauseGame();

		sf::Vector2f getWindowSize();

		pong::PongBall* createBall(sf::Vector2f centerWindow);
		pong::PongPaddle* createPaddle(sf::Vector2f placement,
			sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, bool isLeftBounce);

		bool isRoundRunning();
	};
}

