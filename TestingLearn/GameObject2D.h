#pragma once
#include <iostream>
#include <random>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "GameApp.h"

namespace pong
{
	class GameObject2D
	{
	private:
		sf::RenderWindow* window;
		sf::Vector2f position;

		unsigned long long objectID = 0ULL;

		/// <summary>
		/// Generate random ULL for object Id.
		/// </summary>
		/// <returns>Object ID</returns>
		static unsigned long long getRandomID();

	protected:
		sf::RenderWindow* getWindow();

	public:
		GameObject2D(sf::RenderWindow* window);

		~GameObject2D();
		GameObject2D(GameObject2D const& objRef);
		GameObject2D& operator=(GameObject2D const& objRef);

		void setPosition(sf::Vector2f pos);
		void setPosition(float x, float y);
		sf::Vector2f getPosition();

		unsigned long long getObjectID();

		/// <summary>
		/// Draw a shape to target window.
		/// </summary>
		/// <param name="shape">Target shape</param>
		void onWindowDraw(sf::Shape* shape);
	};
}

