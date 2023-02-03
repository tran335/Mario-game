#include "Piranha.h"

CPiranha::CPiranha(float x, float y)
{
	this->x = x;
	this->y = y;
	start_y = y;
	start_time = 0;
	vy = -PIRANHA_SPEED;
}

void CPiranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy;
	if (start_time == 0) {
		if (y < start_y - PIRANHA_HEIGHT) {
			vy = 0.0f;
			startTime();
		}
	}
	
	else if (GetTickCount64() - start_time > GROW_UP_TIME and start_time >0) {
		start_time = 0;
		vy =  PIRANHA_SPEED;
	}
		if (y >= start_y + PIRANHA_HEIGHT_DOWN) {
		vy = -PIRANHA_SPEED;
	}
	

	CGameObject::Update(dt, coObjects);

}

void CPiranha::Render()
{
	int aniId = IC_ANI_PIRANHA;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}



void CPiranha::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIRANHA_BBOX_WIDTH / 2;
	t = y - PIRANHA_BBOX_HEIGHT / 2;
	r = l + PIRANHA_BBOX_WIDTH;
	b = t + PIRANHA_BBOX_HEIGHT;
}


