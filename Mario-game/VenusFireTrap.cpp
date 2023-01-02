#include "VenusFireTrap.h"

CVenusFireTrap::CVenusFireTrap(float x, float y)
{
	this->x = x;
	this->y = y;
	start_y = y;
	vy = -VENUS_SPEED;
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

void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy;

	if (isShooting == false) {
		if (y < start_y - VENUS_HEIGHT) // have not overlap with pipe
		{
			vy = 0.0f;
			StartShootTime();
		}
	}
	else if (GetTickCount64() - shootingStartTime > VENUS_SHOOTING_TIME) {
		shootingStartTime = 0;
		isShooting = false;
		vy = VENUS_SPEED;
	}
	if (y > start_y + VENUS_HEIGHT) {
		vy = -VENUS_SPEED;
	}
	CGameObject::Update(dt, coObjects);
}

void CVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - VENUS_BBOX_WIDTH / 2;
	t = y - VENUS_BBOX_HEIGHT / 2;
	r = l + VENUS_BBOX_WIDTH;
	b = t + VENUS_BBOX_HEIGHT;
}

void CVenusFireTrap::StartShootTime()
{
	isShooting = true;
	shootingStartTime = GetTickCount64();
}
