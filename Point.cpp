#include "Point.h"

// Operator to check if two point's current location are in EXPLODE_RADIUS (2) units from each other
bool Point::operator%(const Point& other) const
{
	int dx = std::abs(this->x - other.x);
	int dy = std::abs(this->y - other.y);
	return (dx <= EXPLODE_RADIUS) && (dy <= EXPLODE_RADIUS);
}