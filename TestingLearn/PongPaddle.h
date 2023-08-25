#pragma once
#include <iostream>
#include <cmath>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Velocity2D.h"

namespace pong
{
	class PongPaddle final : public GameObject2D, public Runtime
	{
	private:
		Velocity2D* velocityHandler;
		sf::RectangleShape shape;

	public:
		PongPaddle(sf::RenderWindow* window, sf::Vector2f paddleSize);
		PongPaddle(sf::RenderWindow* window, float sizeX, float sizeY);

		~PongPaddle();
		PongPaddle(PongPaddle const& ballRef);
		PongPaddle& operator=(PongPaddle const& ballRef);

		void onAwake();
		void onUpdate();
		void onEnd();
	};
}
