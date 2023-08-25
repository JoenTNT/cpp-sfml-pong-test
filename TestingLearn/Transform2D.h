#pragma once
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace pong
{
	class Transform2D
	{
	private:
		sf::RenderWindow* window;
		sf::Vector2f position;

	public:
		Transform2D(sf::RenderWindow* window);

		~Transform2D();
		Transform2D(Transform2D const& objRef);
		Transform2D& operator=(Transform2D const& objRef);

		void setPosition(sf::Vector2f pos);
		void setPosition(float x, float y);
		sf::Vector2f getPosition();

		/// <summary>
		/// Draw a shape to target window.
		/// </summary>
		/// <param name="shape">Target shape</param>
		void onWindowDraw(sf::Shape* shape);
	};
}

