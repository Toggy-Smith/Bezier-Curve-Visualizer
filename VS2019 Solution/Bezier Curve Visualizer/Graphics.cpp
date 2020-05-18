#include "Graphics.hpp"

Graphics::Graphics
(sf::RenderWindow& window, Logic& logic)
	: m_window(window), m_logic(logic), m_viewManager(window), m_line(window)
{
	///
}

void Graphics::detectNumberKeyReleased
(sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Num2) {
			m_logic.m_numberOfControlPointsVisible = 2;

			m_logic.m_interpolationClock.restart();

			m_logic.m_trail.clear();
		} else if (event.key.code == sf::Keyboard::Num3) {
			m_logic.m_numberOfControlPointsVisible = 3;

			m_logic.m_interpolationClock.restart();

			m_logic.m_trail.clear();
		} else if (event.key.code == sf::Keyboard::Num4) {
			m_logic.m_numberOfControlPointsVisible = 4;

			m_logic.m_interpolationClock.restart();

			m_logic.m_trail.clear();
		}
	}
}

void Graphics::handleEvent
(sf::Event& event)
{
	m_viewManager.handleEvent(event);

	detectNumberKeyReleased(event);
}

void Graphics::render() {
	// Draw lines between the control points
	for (int i = 0; i < m_logic.m_numberOfControlPointsVisible - 1; i++) {
		sf::Vector2f controlPoint1Position{ m_logic.m_controlPoints[i].x,
											m_logic.m_controlPoints[i].y };

		sf::Vector2f controlPoint2Position{ m_logic.m_controlPoints[i + 1].x,
											m_logic.m_controlPoints[i + 1].y };

		m_line.draw(controlPoint1Position, controlPoint2Position, sf::Color(76, 76, 76), 10);
	}

	// Draw curve
	sf::CircleShape circleShape;

	circleShape.setRadius(5.0f);
	circleShape.setOrigin(sf::Vector2f(circleShape.getRadius(), circleShape.getRadius()));

	circleShape.setFillColor(sf::Color(219, 78, 64));

	for (unsigned int i = 0; i < m_logic.m_trail.size(); i++) {
		circleShape.setPosition(m_logic.m_trail[i]);

		m_window.draw(circleShape);
	}

	// Draw the control points
	circleShape.setRadius((float) m_logic.m_controlPointRadius);
	circleShape.setOrigin(sf::Vector2f(circleShape.getRadius(), circleShape.getRadius()));

	for (int i = 0; i < m_logic.m_numberOfControlPointsVisible; i++) {
		circleShape.setPosition(sf::Vector2f(m_logic.m_controlPoints[i].x, m_logic.m_controlPoints[i].y));

		if (m_logic.m_controlPoints[i].isBeingDragged)
			circleShape.setFillColor(sf::Color(242, 232, 99));
		else
			circleShape.setFillColor(sf::Color(128, 141, 158));

		m_window.draw(circleShape);
	}

	for (unsigned int i = 0; i < m_logic.m_controlPoints.size(); i++) {
		if (m_logic.m_controlPoints[i].isBeingDragged)
			return;
	}

	// Draw the interpolation points
	circleShape.setRadius((float) m_logic.m_controlPointRadius / 1.5f);

	circleShape.setOrigin(sf::Vector2f(circleShape.getRadius(), circleShape.getRadius()));

	if (m_logic.m_numberOfControlPointsVisible >= 3)
		m_line.draw(m_logic.m_interpolationPoint1, m_logic.m_interpolationPoint2, sf::Color(63, 173, 88), (int) ((float) m_logic.m_controlPointRadius / 1.5f));
	
	if (m_logic.m_numberOfControlPointsVisible == 4)
		m_line.draw(m_logic.m_interpolationPoint2, m_logic.m_interpolationPoint3, sf::Color(63, 173, 88), (int) ((float) m_logic.m_controlPointRadius / 1.5f));

	circleShape.setPosition(m_logic.m_interpolationPoint1);
	m_window.draw(circleShape);

	if (m_logic.m_numberOfControlPointsVisible >= 3) {
		circleShape.setPosition(m_logic.m_interpolationPoint2);
		m_window.draw(circleShape);
	}

	if (m_logic.m_numberOfControlPointsVisible == 3) {
		circleShape.setPosition(m_logic.m_interpolationPoint4);
		m_window.draw(circleShape);
	}

	if (m_logic.m_numberOfControlPointsVisible == 4) {
		circleShape.setPosition(m_logic.m_interpolationPoint3);
		m_window.draw(circleShape);

		m_line.draw(m_logic.m_interpolationPoint4, m_logic.m_interpolationPoint5, sf::Color(64, 71, 249), (int) ((float) m_logic.m_controlPointRadius / 1.5f));

		circleShape.setPosition(m_logic.m_interpolationPoint4);
		m_window.draw(circleShape);

		circleShape.setPosition(m_logic.m_interpolationPoint5);
		m_window.draw(circleShape);

		// Draw final interpolation point
		circleShape.setPosition(m_logic.m_interpolationPoint6);
		m_window.draw(circleShape);
	}
}