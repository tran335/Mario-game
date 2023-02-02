#include "OverworldBound.h"

COverworldBound::COverworldBound(float width, float height)
{
	this->width = width;
	this->height = height;
}

void COverworldBound::Render()
{
	//RenderBoundingBox();
}

void COverworldBound::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width;
	b = t + height;
}
