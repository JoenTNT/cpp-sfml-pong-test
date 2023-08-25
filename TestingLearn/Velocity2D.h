#pragma once
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Time.h"
#include "Runtime.h"
#include "Transform2D.h"

namespace pong
{
	/// <summary>
	/// Handles transform velocity movement.
	/// </summary>
	class Velocity2D final : public Runtime
	{
	private:
		Transform2D* transform;
		sf::Vector2f direction;

	public:
		Velocity2D(Transform2D* transform);
		~Velocity2D();

		void setDirection(sf::Vector2f dir);
		void setDirection(float x, float y);
		sf::Vector2f getDirection();

		void onAwake();
		void onUpdate();
		void onEnd();
	};
}
