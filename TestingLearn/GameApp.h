#pragma once
#include <iostream>
#include <cstdlib>
#include <unordered_map>

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
		std::unordered_map<unsigned long long, Runtime*> runtimeEntities;

		sf::Vector2i windowSize;
		sf::RectangleShape* background;

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

		static bool isObjectWithIDExists(unsigned long long id);

		void onAwake();
		void onUpdate();
		void onEnd();
	};
}
