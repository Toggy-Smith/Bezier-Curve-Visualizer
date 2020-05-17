#pragma once

#include "ControlPoint.hpp"

#include "SFML/Graphics.hpp"

#include <array>
#include <cmath>
#include <tuple>
#include <vector>

class Logic {
	public:
		sf::RenderWindow&           m_window;

		std::array<ControlPoint, 4> m_controlPoints;

		int                         m_controlPointRadius = 20;

		sf::Clock                   m_interpolationClock;

		sf::Vector2f                m_interpolationPoint1,
			                        m_interpolationPoint2,
			                        m_interpolationPoint3,
			                        m_interpolationPoint4,
			                        m_interpolationPoint5,
			                        m_interpolationPoint6;

		std::vector<sf::Vector2f>   m_trail;

		int                         m_numberOfControlPointsVisible = 4;

	public:
		Logic(sf::RenderWindow&);

		std::tuple<bool, unsigned int> controlPointClicked           ();

		void                           detectLeftMouseButtonPressed  (sf::Event&);
		void                           detectMouseMoved              (sf::Event&);
		void                           detectLeftMouseButtonReleased (sf::Event&);
		void                           handleEvent                   (sf::Event&);

		void                           update                        ();
};