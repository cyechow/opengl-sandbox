#pragma once

#include "DrawableBase.h"
#include "Point.h"

class TriangleDrawable :		public DrawableBase
{
	typedef						DrawableBase					BaseClass;

public:
	TriangleDrawable();
	~TriangleDrawable();

	void						InitGL( const Point& A, const Point& B, const Point& C );
	void						UpdateGL();
	virtual void				FiniGL() override;
	virtual void				DrawGL() override;

private:
	unsigned int				m_iPositionBuffer;
	unsigned int				m_iColorBuffer;
};
