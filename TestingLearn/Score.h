#pragma once
#include <iostream>
#include <cstdlib>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Interfaces/IRenderUI.h"
#include "GameObject2D.h"

namespace pong
{
	/// <summary>
	/// Handle display score.
	/// </summary>
	class Score final : public GameObject2D, public IRenderUI
	{
	private:
		sf::Text* text;
		sf::Font font;
		int value = 0;

	public:
		Score(sf::RenderWindow* window, std::string fontFile);

		~Score();
		Score(Score const& arg);
		pong::Score& operator=(Score const& arg);

		void render();
		
		sf::Vector2f getBoundSize();
		void setScore(int value);
		int getScore();

		bool operator>(Score const& comp);
		bool operator<(Score const& comp);
		bool operator>=(Score const& comp);
		bool operator<=(Score const& comp);
		bool operator==(Score const& comp);
		bool operator!=(Score const& comp);
	};
}
