#pragma once

#include "Point.h"

class Edge
{
public:
	Edge( const Point start, const Point end);
	~Edge();

private:
	const Point m_Start;
	const Point m_End;
};
