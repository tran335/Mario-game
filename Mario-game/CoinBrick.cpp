#include "CoinBrick.h"



CCoinBrick::CCoinBrick()
{
	this->x = x;
	this->y = y;
	start_y = y;
}


void CCoinBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CCoinBrick*>(e->obj)) return;

}
void CCoinBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetState() == COINBRICK_STATE_THROW_UP)
	{
		if (jumpTime == 0) {
			BrickStartToThrow();
		}
		else if (GetTickCount64() - jumpTime > JUMP_TIME && jumpTime>0) {
			if (y < start_y) 
			{
				vy = CONINBRICK_RETURN_START_POS_VY;
				y = vy * dt;
			}
			else
			{
				y = start_y;
				vy = 0;
				jumpTime = 0;
			}
		}

	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCoinBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int ani = ID_ANI_COINBRICK;
	animations->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CCoinBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COINBRICK_BBOX_WIDTH / 2;
	t = y - COINBRICK_BBOX_HEIGHT / 2;
	r = l + COINBRICK_BBOX_WIDTH;
	b = t + COINBRICK_BBOX_HEIGHT;
}
void CCoinBrick::SetState(int state)
{

	CGameObject::SetState(state);
	switch (state)
	{
	case COINBRICK_STATE_THROW_UP:
		vx = 0;
		vy = -COINBRICK_JUMP_SPEED_Y;
		y +=vy;
		break;
	}
}