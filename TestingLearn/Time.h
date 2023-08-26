#pragma once
#include <iostream>
#include <chrono>

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
		sf::Time time;
		float fixedDeltaTime = 1.f / 60.f;
		float t = 0.f;

		Time();
		
		/// <summary>
		/// Singleton implementation.
		/// </summary>
		/// <returns>Singleton instance.</returns>
		static Time& getInstance();

		~Time();
		Time(Time const&) = delete;
		void operator=(Time const&) = delete;

	public:
		static float getFixedDelta();
		static void setFixedDelta(float fixedDeltaTime);
		static float getElapsedDelta();
		static void tick();
	};
}
