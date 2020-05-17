#pragma once

#include "SFML/Graphics.hpp"

class ViewManager {
	private:
		sf::RenderWindow& m_window;

		bool              m_isViewBeingPanned         = false;
		sf::Vector2f      m_viewLastMousePanPosition;

	public:
		     ViewManager                    (sf::RenderWindow&);

		void adjustViewSize                 ();
		void detectRightMouseButtonPressed  (sf::Event&);
		void detectMouseMoved               (sf::Event&);
		void detectRightMouseButtonReleased (sf::Event&);
		void handleEvent                    (sf::Event&);
};