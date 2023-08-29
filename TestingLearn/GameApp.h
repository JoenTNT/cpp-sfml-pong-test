#pragma once
#include <iostream>
#include <cstdlib>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

//#include "PongBall.h"
//#include "PongPaddle.h"
#include "Systems/GameSystem.h"

namespace pong
{
	class GameApp final : public IRuntime
	{
	private: // Variables
		GameSystem* gameSystem;
		sf::RenderWindow* mainWindow;
		sf::RectangleShape* background;

		sf::Text scoreText;
		sf::Font font;

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
