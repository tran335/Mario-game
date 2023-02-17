#include "PortalPipe.h"

#include "Game.h"
#include "Textures.h"



CPortalPipe::CPortalPipe(float x, float y, float width, float height, int type)
{
	this->type = type;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


void CPortalPipe::Render()
{
	RenderBoundingBox();
}

void CPortalPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width;
	b = b + height;
}
