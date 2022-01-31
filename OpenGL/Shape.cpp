#include "Shape.h"

Shape::Shape()
{}

Shape::Shape( std::vector<Point> apPoints ) :
	m_apPoints( apPoints )
{}

Shape::~Shape()
{
}
