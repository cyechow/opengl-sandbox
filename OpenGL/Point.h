#pragma once

#include "Geometry.h"

#include <Eigen/Dense>

class Point :				public Geometry
{
	typedef					Geometry									BaseClass;

public:
	Point();
	Point( double x, double y, double z);
	~Point();

	const Eigen::Vector3d	GetVertex() const							{ return GetTransform() * m_vPoint; }

	const double			X() const									{ return GetVertex().x(); }
	const double			Y() const									{ return GetVertex().y(); }
	const double			Z() const									{ return GetVertex().z(); }

	virtual void			Scale( double dScale )						{ return; }; // no-op, point can't be scaled
	virtual void			Rotate( Eigen::Quaterniond qRotate );
	virtual void			Rotate( Eigen::AngleAxisd vAxis, Eigen::Vector3d vRotate );
	virtual void			Translate( Eigen::Vector3d vTranslate );

private:
	Eigen::Vector3d			m_vPoint;
};
