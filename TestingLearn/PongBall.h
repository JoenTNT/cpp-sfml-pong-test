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
	class PongBall final : public GameObject2D, public Runtime
	{
	private:
		Velocity2D* velocityHandler;
		sf::CircleShape shape;

		float moveSpeed = 0.f;
		float accelerateSpeed = 2.f;

	public:
		PongBall(sf::RenderWindow* window, float ballRadius);

		~PongBall();
		PongBall(PongBall const& ballRef);
		PongBall& operator=(PongBall const& ballRef);

		float getRadius();
		float getDiameter();

		void setSpeed(float speed);
		float getSpeed();
		void setAccelerate(float accelerate);
		float getAccelerate();

		/// <summary>
		/// Bounce function against something on x axis.
		/// </summary>
		void bounceX();

		/// <summary>
		/// Bounce function against something on y axis.
		/// </summary>
		void bounceY();

		void onAwake();
		void onUpdate();
		void onEnd();
	};
}
