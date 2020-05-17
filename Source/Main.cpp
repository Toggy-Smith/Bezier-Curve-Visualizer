#include "SFML/Graphics.hpp"

#include "Controller.hpp"

int main() {
	const int         WINDOW_WIDTH  { 800 };
	const int         WINDOW_HEIGHT { 600 };
	const std::string WINDOW_TITLE  { "Bezier Curve Visualizer" };
	
	sf::RenderWindow  window        { sf::VideoMode(WINDOW_WIDTH
		                            , WINDOW_HEIGHT), WINDOW_TITLE };

	Controller        controller    { window };

	while (window.isOpen()) {
		controller.handleEvents();

		controller.update();

		controller.render();
	}

	return 0;
}