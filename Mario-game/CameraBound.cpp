#include "CameraBound.h"


CCameraBound::CCameraBound(float width, float height)
{
	this->width = width;
	this->height = height;
}

void CCameraBound::Render()
{
	//RenderBoundingBox();
}

void CCameraBound::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width;
	b = t + height;
}