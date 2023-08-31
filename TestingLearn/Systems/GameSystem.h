#pragma once
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Score.h"
#include "../PongPaddle.h"
#include "../UIContainer.h"

namespace pong
{
	/// <summary>
	/// Contains all the game status.
	/// </summary>
	struct GameStatus {
		bool isStarting = false;
		bool isRunning = false;
	};

	class GameSystem final
	{
	private:
		sf::RenderWindow* window;
		PongPaddle* playerOne = nullptr;
		PongPaddle* playerTwo = nullptr;
		PongBall* ball = nullptr;
		Score* scoreP1 = nullptr;
		Score* scoreP2 = nullptr;

		std::function<void(const OnBallScoreEventArgs&)> onBallScoreFunc;
		Subscriber* onBallScoreEvSubs = nullptr;

		GameStatus status;
		float initialBallSpeed = 250.f;
		float ballRunIn = 3.f; // In Seconds.
		float tempBallRunIn = 0.f;

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
		pong::Score* createScore(sf::Vector2f placement, std::string fontFile);

		void addP1Score(int a);
		void addP2Score(int a);

		bool isRoundCountdown();
		bool isRoundRunning();
	};
}

