#pragma once

#include <vector>

#include "Point.h"
#include "Edge.h"

class Shape
{
public:
	Shape();
	Shape( std::vector<Point> aPoints );
	virtual ~Shape();

	const std::vector<Point>		GetPoints() const		{ return m_apPoints; }
	// Get triangles for mesh?

private:
	std::vector<Point>				m_apPoints;
};
