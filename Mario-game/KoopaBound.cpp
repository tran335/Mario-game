#include "KoopaBound.h"


CKoopaBound::CKoopaBound(float width, float height)
{
	this->width = width;
	this->height = height;
}

void CKoopaBound::Render()
{
	//RenderBoundingBox();
}

void CKoopaBound::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - KOOPABOUND_BBOX_WIDTH/2;
	t = y - KOOPABOUND_BBOX_HEIGHT/2;
	r = l + width;
	b = t + height;
}