#pragma once
#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

//#include "PongBall.h"
//#include "PongPaddle.h"
#include "UIContainer.h"
#include "Systems/GameSystem.h"

#define LIMIT_MID_LINE_CIRCLE 20

namespace pong
{
	class GameApp final : public IRuntime
	{
	private: // Variables
		std::unique_ptr<GameSystem> gameSystem;
		sf::RenderWindow* mainWindow;
		sf::RectangleShape* background;

		sf::CircleShape midLine[LIMIT_MID_LINE_CIRCLE];

		bool isAppRunning = true;

	public: // Variables
		const int minWindowWidth = 640;
		const int minWindowHeight = 360;

		sf::Color windowColor;

	private: // Functions
		GameApp();
		~GameApp();

		GameApp(GameApp const&) = delete;
		void operator=(GameApp const&) = delete;

	public: // Functions
		/// <summary>
		/// Singleton implementation.
		/// </summary>
		/// <returns>Singleton instance.</returns>
		static GameApp& getInstance();

		static sf::Vector2i getWindowSize();
		bool isRunning();

		void onAwake();
		void onUpdate();
		void onEnd();
	};
}
