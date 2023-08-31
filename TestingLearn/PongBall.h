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
	/// <summary>
	/// Event argument when the ball score where between 2 side.
	/// </summary>
	struct OnBallScoreEventArgs : Event {
		bool leftGoal = false;
		bool rightGoal = false;

		OnBallScoreEventArgs(bool left, bool right) : leftGoal(left), rightGoal(right) { }
	};

	class PongBall final : public GameObject2D, public IRuntime
	{
	private:
		const float limitDegreeOnY = 70.f;

		Velocity2D* velocityHandler;
		sf::CircleShape shape;

		std::unordered_multimap<const void*, std::function<void(const Event&)>> onBallScoreEvCont;
		Invoker* onBallScoreEvInvk;

		float moveSpeed = 225.f;
		float accelerateSpeed = 8.f;

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

		void setVelocity(sf::Vector2f dir);
		void accelerate();

		/// <summary>
		/// Bounce function against something on x axis.
		/// </summary>
		void bounceX();

		/// <summary>
		/// Bounce function against something on y axis.
		/// </summary>
		void bounceY();

		/// <summary>
		/// This will create a subscriber from the event container.
		/// </summary>
		/// <returns></returns>
		Subscriber* createOnBallScoreEvSubs();

		void onAwake();
		void onUpdate();
		void onEnd();

		sf::Vector2f getRandomDir();
	};
}
