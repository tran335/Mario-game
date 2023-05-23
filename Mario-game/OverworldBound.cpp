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
	l = x - BOUND_BBOX_WIDTH/2;
	t = y - BOUND_BBOX_HEIGHT/2;
	r = l + width;
	b = t + height;
}