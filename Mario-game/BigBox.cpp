#include "BigBox.h"

CBigBox::CBigBox(float width, float height)
{
	this->width = width;
	this->height = height;
}

void CBigBox::Render()
{
	//RenderBoundingBox();
}

void CBigBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BIGBOX_BBOX_WIDTH/2;
	t = y - BIGBOX_BBOX_HEIGHT/2;
	r = l + width;
	b = t;
}



