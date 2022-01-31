#include "Point.h"

Point::Point() :
	BaseClass(),
	m_vPoint( 0, 0, 0 )
{}

Point::Point( double x, double y, double z ) :
	BaseClass(),
	m_vPoint( x, y, z )
{}

Point::~Point()
{
}

void
Point::Rotate( Eigen::Quaterniond qRotate )
{
}

void
Point::Rotate( Eigen::AngleAxisd vAxis, Eigen::Vector3d vRotate )
{
}

void
Point::Translate( Eigen::Vector3d vTranslate )
{
}
