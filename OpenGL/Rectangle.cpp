#include "Rectangle.h"

Rectangle::Rectangle() :
	BaseClass()
{
}

Rectangle::Rectangle( std::vector<Point> aPoints ) :
	BaseClass( aPoints )
{
}

Rectangle::~Rectangle()
{
}

const Point&
Rectangle::GetPointAtIndex( int iIndex ) const
{
	if ( iIndex > 3 ) return Point();

	return GetPoints().at( iIndex );
}
