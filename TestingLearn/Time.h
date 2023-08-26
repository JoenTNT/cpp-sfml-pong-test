#pragma once
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace pong
{
	/// <summary>
	/// Static instance of time in game.
	/// </summary>
	class Time final
	{
	private:
		sf::Clock clock;
		sf::Time deltaTime;

	private:
		Time();
		~Time();

		/// <summary>
		/// Singleton implementation.
		/// </summary>
		/// <returns>Singleton instance.</returns>
		static Time& getInstance();

		Time(Time const&) = delete;
		void operator=(Time const&) = delete;

	public:
		static void init();
		static float getSecondsDelta();
		static void tick();
	};
}
