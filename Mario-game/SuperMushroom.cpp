#include "SuperMushroom.h"
#include "PlayScene.h"
#include "Platform.h"
#include "QuestionBrick.h"

CSuperMushroom::CSuperMushroom(float x, float y) :CGameObject(x, y)
{
	this->y = y;
	this->x = x;
	this->ax = 0;
	direct_time = -1;
	this->ay = SUPERMUSHROOM_GRAVITY;
	start_y = y;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CSuperMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x - SUPERMUSHROOM_BBOX_WIDTH / 2;
		top = y - SUPERMUSHROOM_BBOX_HEIGHT / 2;
		right = left + SUPERMUSHROOM_BBOX_WIDTH;
		bottom = top + SUPERMUSHROOM_BBOX_HEIGHT;
}

void CSuperMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CSuperMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
		if (dynamic_cast<CQuestionBrick*>(e->obj))
			OnCollisionWithQuestionBrick(e);
		else if (dynamic_cast<CMario*>(e->obj))
			OnCollisionWithQuestionBrick(e);
}
void CSuperMushroom::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionbrick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->ny < 0 && state == LEAF_STATE_FLY) {
		isCollision = false;
	}
	else 
		isCollision = true;
}
void CSuperMushroom::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(e->obj);
	if (e->ny < 0) {
		isCollision = true;
	}
}
void CSuperMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == SUPERMUSHROOM_STATE_WALKING) {
	vy += ay * dt;
	vx += ax * dt;
	if (y < start_y - SUPERMUSHROOM_BBOX_HEIGHT) {
			vy = 0.0f;
			y = start_y - SUPERMUSHROOM_BBOX_HEIGHT;
		}
	}
	else if (state == LEAF_STATE_FLY) {
			vy = ay * dt;
			if (isRight == true) {
				if (GetTickCount64() - direct_time > DIRECT_TIME && direct_time > 0) {
					direct_time = 0;
					isRight = false;
					isDirect = false;
				}
				else {
					vx = ax * dt;
					if (isDirect == false) {
						startDirect();
					}
				}
			}
			else {
				if (GetTickCount64() - direct_time > DIRECT_TIME && direct_time > 0) {
					isRight = true;
					isDirect = false;
					direct_time = 0;
				}
				else {
					vx = -ax * dt;
					if (isDirect == false) {
						startDirect();
					}
				}
			}
	
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CSuperMushroom::Render()
{
	int aniId = -1;
	if (mario->GetLevel() < MARIO_LEVEL_BIG) 
	{
		 aniId = ID_ANI_SUPERMUSHROOM_WALKING;
	}
	else 
	{
		if (isRight != true)
			aniId = ID_ANI_LEAF;
		else
			aniId = ID_ANI_LEAF_RIGHT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CSuperMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SUPERMUSHROOM_STATE_WALKING:
		vy = -SUPERMUSHROOM_BBOX_HEIGHT;
		vx = -SUPERMUSHROOM_WALKING_SPEED;
		break;
	case LEAF_STATE_FLY:
		y = start_y - MAX_Y;
		ay = LEAF_GRAVITY_AY;
		ax = LEAF_GRAVITY_AX;
		break;
	}
}
