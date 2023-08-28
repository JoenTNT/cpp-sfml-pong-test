#pragma once
#include <iostream>
#include <functional>
#include <cmath>
#include <unordered_set>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

//#include "Runtime.h"
//#include "GameObject2D.h"
//#include "Velocity2D.h"
#include "PongBall.h"

namespace pong
{
	class PongPaddle final : public GameObject2D, public IRuntime
	{
	private:
		std::unordered_map<unsigned long, PongBall*> ballsOnMap;
		std::unordered_set<unsigned long> ballInsidePaddle;
		Velocity2D* velocityHandler;
		sf::RectangleShape shape;

		Subscriber* onAddRuntimeEvSubs;

		float moveSpeed = 192.f;

		sf::Keyboard::Key upKey = sf::Keyboard::Key::W;
		sf::Keyboard::Key downKey = sf::Keyboard::Key::S;

		bool isUpKeyPressed = false;
		bool isDownKeyPressed = false;

		bool bounceLeft = true; // Bounce from right to left movement.
		bool bounceRight = false; // Bounce from left to right movement.

		void checkBall(PongBall* ball);
		bool isBallOnYHit(sf::Vector2f ballPos, sf::Vector2f paddlePos, float ballDiameter, 
			float paddleHeight);

		std::function<void(const OnAddRuntimeEventArgs&)> onAddRuntimeFunc;

	public:
		PongPaddle(sf::RenderWindow* window, sf::Vector2f paddleSize);
		PongPaddle(sf::RenderWindow* window, float sizeX, float sizeY);

		~PongPaddle();
		PongPaddle(PongPaddle const& ballRef);
		PongPaddle& operator=(PongPaddle const& ballRef);

		void setControlKeys(sf::Keyboard::Key up, sf::Keyboard::Key down);

		void setMoveSpeed(float moveSpeed);
		float getMoveSpeed();

		/// <summary>
		/// Get paddle size.
		/// </summary>
		/// <returns>Width and height of paddle.</returns>
		sf::Vector2f getSize();
		float getWidth();
		float getHeight();

		void setBounceLeft();
		void setBounceRight();

		void onAwake();
		void onUpdate();
		void onEnd();
	};
}
