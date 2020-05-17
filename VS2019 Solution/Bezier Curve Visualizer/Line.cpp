#include "Line.hpp"

Line::Line
(sf::RenderWindow& window)
	: m_window(window)
{}
#include <iostream>
void Line::draw
(sf::Vector2f& start, sf::Vector2f& end, const sf::Color& color, int thickness)
{
	float distanceBetweenEnds = std::sqrt(std::pow(start.x - end.x, 2) + std::pow(start.y - end.y, 2));

	m_rectangleShape.setSize(sf::Vector2f((float) thickness, distanceBetweenEnds));
	m_rectangleShape.setOrigin(sf::Vector2f((float) thickness / 2, distanceBetweenEnds));
	m_rectangleShape.setPosition(sf::Vector2f(start));
	m_rectangleShape.setFillColor(color);

	m_rectangleShape.setRotation(std::atan2(start.y - end.y, start.x - end.x) * 180 / (float) 3.14 - 90);

	m_window.draw(m_rectangleShape);
}