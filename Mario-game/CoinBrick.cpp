#include "CoinBrick.h"



CCoinBrick::CCoinBrick()
{
	//this->x = x;
	//this->y = y;
	//start_y = y;
}

void CCoinBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	//if (GetState() == COINBRICK_STATE_THROW_UP)
	//{
	//	if (jumpTime == 0) {
	//		BrickStartToThrow();
	//	}
	//	else if (GetTickCount64() - jumpTime > JUMP_TIME) {
	//		if (y < start_y) // take brick to start_y after deflect cause disable
	//		{
	//			y = y + BRICK_RETURN_START_POS_VY;
	//		}
	//		else
	//		{
	//			y = start_y;
	//			vy = 0;
	//		}
	//	}

	//}
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
//void CCoinBrick::SetState(int state)
//{
//
//	CGameObject::SetState(state);
//	switch (state)
//	{
//	case COINBRICK_STATE_THROW_UP:
//		vx = 0;
//		vy = 0;
//		y = y - COINBRICK_JUMP_SPEED_Y;
//		break;
//	}
//}