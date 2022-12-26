#include "QuestionBrick.h"



CQuestionBrick::CQuestionBrick(float x, float y)
{
	this->x = x;
	this->y = y;
	start_y = y;
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (GetState() == QUESTIONBRICK_STATE_DISABLE)
	{
		if (jumpTime == 0) {
			BrickStartToThrow();
		}
		else if (GetTickCount64() - jumpTime > JUMP_TIME) {
			if (y < start_y) // take brick to start_y after deflect cause disable
			{
				y = y + BRICK_RETURN_START_POS_VY;
			}
			else
			{
				y = start_y;
				vy = 0;
			}
		}

	}
}

void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int ani = ID_ANI_QUESTIONBRICK;
	if (state == QUESTIONBRICK_STATE_DISABLE) {
		ani = ID_ANI_QUESTIONBRICK_DISABLE;
	}
	animations->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTIONBRICK_BBOX_WIDTH / 2;
	t = y - QUESTIONBRICK_BBOX_HEIGHT / 2;
	r = l + QUESTIONBRICK_BBOX_WIDTH;
	b = t + QUESTIONBRICK_BBOX_HEIGHT;
}
void CQuestionBrick::SetState(int state)
{
	
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTIONBRICK_STATE_DISABLE:
		vx = 0;
		vy = 0;
		y = y - QUESTIONBRICK_JUMP_SPEED_Y;
		break;
	}
}