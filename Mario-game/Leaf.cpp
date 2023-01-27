#include "Leaf.h"

CLeaf::CLeaf()
{
	this->x = x;
	this->y = y;
	start_y = y;
}


void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CLeaf*>(e->obj)) return;

}
void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (GetState() == COINBRICK_STATE_THROW_UP)
	{
		if (jumpTime == 0) {
			BrickStartToThrow();
		}
		else if (GetTickCount64() - jumpTime > JUMP_TIME && jumpTime > 0) {
			if (y < start_y) // take brick to start_y after deflect cause disable
			{
				vy = COINBRICK_JUMP_SPEED_Y;
				y += vy;
			}
			else
			{
				y = start_y;
				vy = 0;
			}
		}

	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int ani = ID_ANI_COINBRICK;
	animations->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COINBRICK_BBOX_WIDTH / 2;
	t = y - COINBRICK_BBOX_HEIGHT / 2;
	r = l + COINBRICK_BBOX_WIDTH;
	b = t + COINBRICK_BBOX_HEIGHT;
}
void CLeaf::SetState(int state)
{

	CGameObject::SetState(state);
	switch (state)
	{
	case COINBRICK_STATE_THROW_UP:
		vx = 0;
		vy = -COINBRICK_JUMP_SPEED_Y;
		y += vy;
		break;
	}
}