#include "Logic.hpp"

Logic::Logic(sf::RenderWindow& window)
	: m_window{ window },
	  m_controlPoints{ ControlPoint{100, 347}, ControlPoint{200, 281},
					   ControlPoint{300, 280}, ControlPoint{400, 312} }
{
	///
}

std::tuple<bool, unsigned int> // isControlPointClicked, clickedControlPointIndex
Logic::controlPointClicked() {
	bool         isControlPointClicked    = false;
	unsigned int clickedControlPointIndex = 0;


	sf::Vector2i mousePositionInWindow    = sf::Mouse::getPosition(m_window);

	sf::Vector2i mousePositionInView      = (sf::Vector2i)
		                                    m_window.mapPixelToCoords(mousePositionInWindow);

	for (unsigned int i = 0; i < m_controlPoints.size(); i++) {
		float distanceFromMouseToControlPoint = std::sqrt
		                                        (
			                                    std::pow
												(
								                m_controlPoints[i].x - mousePositionInView.x, 2
												)
			                                    +
												std::pow
												(
												m_controlPoints[i].y - mousePositionInView.y, 2
												)
		                                        );

		bool isDistanceLessThanOrEqualToControlPointRadius = distanceFromMouseToControlPoint
			                                               <= m_controlPointRadius;

		if (isDistanceLessThanOrEqualToControlPointRadius) {
			isControlPointClicked = true;

			clickedControlPointIndex = i;
		}
	}


	return std::make_tuple(isControlPointClicked, clickedControlPointIndex);
}

void Logic::detectLeftMouseButtonPressed
(sf::Event& event)
{
	bool leftMouseButtonPressed = event.type == sf::Event::MouseButtonPressed
		                          && event.mouseButton.button == sf::Mouse::Left;

	if (leftMouseButtonPressed) {
		auto [isControlPointClicked, clickedControlPointIndex] = controlPointClicked();

		if (isControlPointClicked) {
			ControlPoint& clickedControlPoint = m_controlPoints[clickedControlPointIndex];
			
			clickedControlPoint.isBeingDragged = true;

			m_trail.clear();
		}
	}
}

void Logic::detectMouseMoved
(sf::Event& event)
{
	bool isMouseMoved = event.type == sf::Event::MouseMoved;

	if (isMouseMoved) {
		for (unsigned int i = 0; i < m_controlPoints.size(); i++) {
			ControlPoint& controlPoint = m_controlPoints[i];

			if (controlPoint.isBeingDragged) {
				sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(m_window);

				sf::Vector2i mousePositionInView   = (sf::Vector2i)
					                                 m_window.mapPixelToCoords(mousePositionInWindow);

				controlPoint.x = (float) mousePositionInView.x;
				controlPoint.y = (float) mousePositionInView.y;
			}
		}
	}
}

void Logic::detectLeftMouseButtonReleased
(sf::Event& event)
{
	bool leftMouseButtonReleased = event.type == sf::Event::MouseButtonReleased
		                         && event.mouseButton.button == sf::Mouse::Left;

	if (leftMouseButtonReleased) {
		for (unsigned int i = 0; i < m_controlPoints.size(); i++) {
			ControlPoint& controlPoint = m_controlPoints[i];

			if (controlPoint.isBeingDragged)
				m_interpolationClock.restart();

			controlPoint.isBeingDragged = false;
		}
	}
}

void Logic::handleEvent
(sf::Event& event)
{
	detectLeftMouseButtonPressed(event);
	detectMouseMoved(event);
	detectLeftMouseButtonReleased(event);
}

sf::Vector2f interpolateBetweenPoints
(sf::Vector2f start, sf::Vector2f end, float interpolationAmount)
{
	float deltaX = end.x - start.x;
	float deltaY = end.y - start.y;

	float xAlong = deltaX * interpolationAmount;
	float yAlong = deltaY * interpolationAmount;

	float x = start.x + xAlong;
	float y = start.y + yAlong;

	return sf::Vector2f(x, y);
}

void Logic::update() {
	const float interpolationSpeed = 2.0f; // measured as number of seconds for one complete interpolation

	if (m_interpolationClock.getElapsedTime().asSeconds() >= interpolationSpeed) {
		m_interpolationClock.restart();

		m_trail.clear();
	}

	for (unsigned int i = 0; i < m_controlPoints.size(); i++) {
		if (m_controlPoints[i].isBeingDragged)
			return;
	}

	m_interpolationPoint1 = interpolateBetweenPoints(sf::Vector2f(m_controlPoints[0].x, m_controlPoints[0].y),
		                                             sf::Vector2f(m_controlPoints[1].x, m_controlPoints[1].y),
		                                             m_interpolationClock.getElapsedTime().asSeconds() / interpolationSpeed);

	m_interpolationPoint2 = interpolateBetweenPoints(sf::Vector2f(m_controlPoints[1].x, m_controlPoints[1].y),
		                                             sf::Vector2f(m_controlPoints[2].x, m_controlPoints[2].y),
		                                             m_interpolationClock.getElapsedTime().asSeconds() / interpolationSpeed);

	m_interpolationPoint3 = interpolateBetweenPoints(sf::Vector2f(m_controlPoints[2].x, m_controlPoints[2].y),
		                                             sf::Vector2f(m_controlPoints[3].x, m_controlPoints[3].y),
		                                             m_interpolationClock.getElapsedTime().asSeconds() / interpolationSpeed);

	m_interpolationPoint4 = interpolateBetweenPoints(m_interpolationPoint1,
		                                             m_interpolationPoint2,
		                                             m_interpolationClock.getElapsedTime().asSeconds() / interpolationSpeed);

	m_interpolationPoint5 = interpolateBetweenPoints(m_interpolationPoint2,
		                                             m_interpolationPoint3,
		                                             m_interpolationClock.getElapsedTime().asSeconds() / interpolationSpeed);

	m_interpolationPoint6 = interpolateBetweenPoints(m_interpolationPoint4,
	                                            	 m_interpolationPoint5,
		                                             m_interpolationClock.getElapsedTime().asSeconds() / interpolationSpeed);

	if (m_numberOfControlPointsVisible == 4)
		m_trail.push_back(m_interpolationPoint6);
	else if (m_numberOfControlPointsVisible == 3)
		m_trail.push_back(m_interpolationPoint4);
	else if (m_numberOfControlPointsVisible == 2)
		m_trail.push_back(m_interpolationPoint1);
}