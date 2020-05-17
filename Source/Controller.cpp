#include "Controller.hpp"

Controller::Controller
(sf::RenderWindow& window)
	: m_window(window), m_graphics(window, m_logic), m_logic(window)
{
	///
}

void Controller::handleEvents() {
	sf::Event event;

	while (m_window.pollEvent(event)) {
		switch (event.type) {
			default:
				break;
			case sf::Event::Closed:
				m_window.close();

				break;
		}

		m_graphics.handleEvent(event);
		m_logic.handleEvent(event);
	}
}

void Controller::update() {
	m_logic.update();
}

void Controller::render() {
	//m_window.clear(sf::Color(234, 242, 227));
	m_window.clear(sf::Color(50, 50, 50));

	m_graphics.render();

	m_window.display();
}