#pragma once

#include "Shape.h"

class Rectangle :					public Shape
{
	typedef							Shape				BaseClass;

public:
	Rectangle();
	Rectangle( std::vector<Point> aPoints );
	virtual ~Rectangle();

	const Point&					GetPointAtIndex( int iIndex ) const;

private:

};
