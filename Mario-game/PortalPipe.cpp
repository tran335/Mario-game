#include "PortalPipe.h"

#include "Game.h"
#include "Textures.h"
#include "PlayScene.h"



CPortalPipe::CPortalPipe(float x, float y, float width, float height, int name, int type)
{
	this->type = type;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}


void CPortalPipe::Render()
{
	//RenderBoundingBox();
}

void CPortalPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PORTAL_BBOX_WIDTH / 2;
	t = y - PORTAL_BBOX_HEIGHT / 2;
	r = l + width;
	b = t + height;
}

