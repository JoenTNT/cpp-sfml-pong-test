#pragma once
#include <iostream>
#include <cmath>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

//#include "Runtime.h"
//#include "GameObject2D.h"
#include "Velocity2D.h"

namespace pong
{
	class PongPaddle final : public GameObject2D, public Runtime
	{
	private:
		Velocity2D* velocityHandler;
		sf::RectangleShape shape;

		float moveSpeed = 192.f;

		sf::Keyboard::Key upKey = sf::Keyboard::Key::W;
		sf::Keyboard::Key downKey = sf::Keyboard::Key::S;

		bool isUpKeyPressed = false;
		bool isDownKeyPressed = false;

	public:
		PongPaddle(sf::RenderWindow* window, sf::Vector2f paddleSize);
		PongPaddle(sf::RenderWindow* window, float sizeX, float sizeY);

		~PongPaddle();
		PongPaddle(PongPaddle const& ballRef);
		PongPaddle& operator=(PongPaddle const& ballRef);

		void setControlKeys(sf::Keyboard::Key up, sf::Keyboard::Key down);

		void setMoveSpeed(float moveSpeed);
		float getMoveSpeed();

		sf::Vector2f getSize();
		float getWidth();
		float getHeight();

		void onAwake();
		void onUpdate();
		void onEnd();
	};
}
