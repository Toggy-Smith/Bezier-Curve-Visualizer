#pragma once

#include "SFML/Graphics.hpp"

#include <cmath>

class Line {
	private:
		sf::RenderWindow&  m_window;

		sf::RectangleShape m_rectangleShape;
	
	public:
		     Line (sf::RenderWindow&);

		void draw (sf::Vector2f&, sf::Vector2f&, const sf::Color&, int);
};