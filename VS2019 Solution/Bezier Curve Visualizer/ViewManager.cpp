#include "ViewManager.hpp"

ViewManager::ViewManager
(sf::RenderWindow& window)
	: m_window(window)
{
	///
}

void ViewManager::adjustViewSize()
{
	sf::View view = m_window.getView();

	view.setSize((sf::Vector2f) m_window.getSize());

	m_window.setView(view);
}

void ViewManager::detectRightMouseButtonPressed
(sf::Event& event)
{
	bool rightMouseButtonPressed = event.type == sf::Event::MouseButtonPressed
		                           && event.mouseButton.button == sf::Mouse::Right;
	
	if (rightMouseButtonPressed) {
		m_isViewBeingPanned = true;

		sf::Vector2f mousePositionInWindow = (sf::Vector2f) sf::Mouse::getPosition(m_window);

		m_viewLastMousePanPosition = mousePositionInWindow;
	}
}

void ViewManager::detectMouseMoved
(sf::Event& event)
{
	bool isMouseMoved = event.type == sf::Event::MouseMoved;

	if (isMouseMoved && m_isViewBeingPanned) {
		sf::Vector2f mousePositionInWindow = (sf::Vector2f) sf::Mouse::getPosition(m_window);
		
		sf::Vector2f deltaMousePosition    = m_viewLastMousePanPosition - mousePositionInWindow;

		sf::View     view                  = m_window.getView();

		view.move(deltaMousePosition);

		m_window.setView(view);

		m_viewLastMousePanPosition = mousePositionInWindow;
	}
}

void ViewManager::detectRightMouseButtonReleased
(sf::Event& event)
{
	bool rightMouseButtonReleased = event.type == sf::Event::MouseButtonReleased
		                          && event.mouseButton.button == sf::Mouse::Right;

	if (rightMouseButtonReleased)
		m_isViewBeingPanned = false;
}

void ViewManager::handleEvent
(sf::Event& event)
{
	detectRightMouseButtonPressed(event);
	detectMouseMoved(event);
	detectRightMouseButtonReleased(event);


	bool isWindowResized = event.type == sf::Event::Resized;

	if (isWindowResized)
		adjustViewSize();
}