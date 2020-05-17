#pragma once

#include "SFML/Graphics.hpp"

typedef struct ControlPoint {
	float x;
	float y;

	bool  isBeingDragged = false;
} ControlPoint;