#pragma once

class DrawableBase
{
public:
	DrawableBase();
	virtual ~DrawableBase();

	void						SetColorGL();

	virtual void				DrawGL()				= 0;
	virtual void				FiniGL()				= 0;

private:

};
