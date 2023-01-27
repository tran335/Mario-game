#include "SuperMushroom.h"
#include "PlayScene.h"

CSuperMushroom::CSuperMushroom(float x, float y) :CGameObject(x, y)
{
	this->y = y;
	this->x = x;
	this->ax = 0;
	this->ay = SUPERMUSHROOM_GRAVITY;
	start_y = y;
	//SetState(SUPERMUSHROOM_STATE_WALKING);
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
	//if (dynamic_cast<CSuperMushroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CMario*>(e->obj))
		OnCollisionWithMario(e);
}
void CSuperMushroom::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	CMario*mario= dynamic_cast<CMario*>(e->obj);
	if (mario->GetLevel() < MARIO_LEVEL_BIG) {
		mario->SetLevel(MARIO_LEVEL_BIG);
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
		aniId = ID_ANI_LEAF;
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
	}
}
