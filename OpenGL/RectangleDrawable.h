#pragma once

#include "DrawableBase.h"

#include "Rectangle.h"

class RectangleDrawable :			public DrawableBase
{
	typedef						DrawableBase				BaseClass;

public:
	RectangleDrawable();
	~RectangleDrawable();

	void						InitGL( const Rectangle& rectGeometry );
	virtual void				DrawGL() override;
	virtual void				FiniGL() override;

private:
	unsigned int				m_iPositionDataBuffer;
	unsigned int				m_iPositionIndexBuffer;
	unsigned int				m_iColorBuffer;
};
