#pragma once

#include "Logic.hpp"
#include "Line.hpp"
#include "ViewManager.hpp"

#include "SFML/Graphics.hpp"

class Graphics {
	private:
		sf::RenderWindow& m_window;

		Logic&            m_logic;

		ViewManager       m_viewManager;

		Line              m_line;

	public:
		     Graphics                (sf::RenderWindow&, Logic&);

	    void detectNumberKeyReleased (sf::Event&);
		void handleEvent             (sf::Event&);
		void render                  ();
};