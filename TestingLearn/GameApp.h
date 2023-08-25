#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "PongBall.h"
#include "Time.h"

namespace pong
{
	class GameApp final : public Runtime
	{
	private: // Variables
		sf::RenderWindow* mainWindow;
		std::vector<Runtime*> runtimeEntities;

		sf::Vector2i windowSize;
		sf::RectangleShape* background;

		int updateEntityIndex = 0, entitySize;
		bool isAppRunning = true;

	public: // Variables
		const int minWindowWidth = 640;
		const int minWindowHeight = 360;

		sf::Color windowColor;

	private: // Functions
		GameApp();
		~GameApp();

	public: // Functions
		/// <summary>
		/// Singleton implementation.
		/// </summary>
		/// <returns>Singleton instance.</returns>
		static GameApp& getInstance();

		GameApp(GameApp const&) = delete;
		void operator=(GameApp const&) = delete;

		static sf::Vector2i getWindowSize();
		bool isRunning();

		void onAwake();
		void onUpdate();
		void onEnd();
	};
}
