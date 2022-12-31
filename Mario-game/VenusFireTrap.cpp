#include "VenusFireTrap.h"

CVenusFireTrap::CVenusFireTrap(float width, float height)
{
	this->width = width;
	this->height = height;
}

void CVenusFireTrap::Render()
{
	int aniId = 0;
	if (isShooting == true) {
		if (isUp == true)
			aniId = ID_ANI_VENUS_SHOOT_UP;
		else
			aniId = ID_ANI_VENUS_SHOOT_DOWN;
	}
	else
		if (isUp == true) {
			aniId = ID_ANI_VENUS_UP;
		}
		else
			aniId = IC_ANI_VENUS_DOWN;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CVenusFireTrap::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void CVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - VENUS_BBOX_WIDTH / 2;
	t = y - VENUS_BBOX_HEIGHT / 2;
	r = l + VENUS_BBOX_WIDTH;
	b = t + VENUS_BBOX_HEIGHT;
}
