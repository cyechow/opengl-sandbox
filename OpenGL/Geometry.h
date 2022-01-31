#pragma once

#include <Eigen/Dense>

/// <summary>
/// Base geometry class that's meant to be templated.
/// Each inherited geometry class will determine the physical shape.
/// All geometries can have a transformation applied to it.
/// The transformation function can be overridden but the transformation matrix is stored in this base class.
/// </summary>
class Geometry
{
public:
	Geometry() : m_mdTransformation( 0, 0, 0, 0 ) {};
	virtual ~Geometry() {};

	virtual void							Scale( double dScale )												= 0;
	virtual void							Rotate( Eigen::Quaterniond qRotate )								= 0; // Rotate about an axis
	virtual void							Rotate( Eigen::AngleAxisd vAxis, Eigen::Vector3d vRotate )			= 0; // Rotate about an axis
	virtual void							Translate( Eigen::Vector3d vTranslate )								= 0;

protected:
	const Eigen::Quaterniond&				GetTransform() const												{ return m_mdTransformation; }
	void									SetTransform( Eigen::Quaterniond qTransform )						{ m_mdTransformation = qTransform; }
	virtual void							TransformGeometry( Eigen::Quaterniond qTransform );

private:
	Eigen::Quaterniond m_mdTransformation;
};
