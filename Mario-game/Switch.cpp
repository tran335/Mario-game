#include "Switch.h"

CSwitch::CSwitch(float x, float y)
{
	this->x = x;
	this->y = y;
	start_y = y;
	jumpTime = 0;
}

void CSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CSwitch::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int ani = ID_ANI_SWITCH;
	if (state == SWITCH_STATE_DIE) {
		ani = ID_ANI_SWITCH_DIE;
	}
	animations->Get(ani)->Render(x, y);
	RenderBoundingBox();
}

void CSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SWITCH_BBOX_WIDTH / 2;
	t = y - SWITCH_BBOX_HEIGHT / 2;
	r = l + SWITCH_BBOX_WIDTH;
	b = t + SWITCH_BBOX_HEIGHT;
}
void CSwitch::SetState(int state)
{

	CGameObject::SetState(state);
	switch (state)
	{
	case SWITCH_STATE_JUMP:
		DebugOut(L"SWITCH JUMP");
		y = y - SWITCH_BBOX_HEIGHT;
		break;
	case SWITCH_STATE_DIE:
		vx = 0;
		vy = 0;
		y += (SWITCH_BBOX_HEIGHT- SWITCH_BBOX_HEIGHT_DIE)/2;
		break;
	}
}