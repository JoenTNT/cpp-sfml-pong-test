#pragma once
#include <iostream>
#include <cstdlib>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "GameObject2D.h"

namespace pong
{
	/// <summary>
	/// Handle display score.
	/// </summary>
	class Score final : public GameObject2D
	{
	private:
		sf::Text* text;
		sf::Font font;
		int value = 0;

	public:
		Score(sf::RenderWindow* window, std::string fontFile);

		~Score();
		Score(Score const& arg);
		void operator=(Score const& arg);
		
		void setScore(int value);
		float getScore();

		bool operator>(Score const& comp);
		bool operator<(Score const& comp);
		bool operator>=(Score const& comp);
		bool operator<=(Score const& comp);
		bool operator==(Score const& comp);
		bool operator!=(Score const& comp);
	};
}
