#pragma once

#include "Graphics.hpp"
#include "Logic.hpp"

#include "SFML/Graphics.hpp"

class Controller {
	private:
		sf::RenderWindow& m_window;

		Graphics          m_graphics;
		Logic             m_logic;

	public:
		     Controller   (sf::RenderWindow&);

		void handleEvents ();
		void update       ();
		void render       ();
};