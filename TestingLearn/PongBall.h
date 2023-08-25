#pragma once
#include <iostream>
#include <cmath>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Velocity2D.h"

namespace pong
{
	class PongBall final : public GameObject2D, public Runtime
	{
	private:
		Velocity2D* velocityHandler;
		sf::CircleShape shape;

	public:
		float moveSpeed = 5.f;

	public:
		PongBall(sf::RenderWindow* window, float ballRadius);

		~PongBall();
		PongBall(PongBall const& ballRef);
		PongBall& operator=(PongBall const& ballRef);

		Velocity2D* getVelocity();
		float getRadius();
		float getDiameter();

		void onAwake();
		void onUpdate();
		void onEnd();
	};
}
