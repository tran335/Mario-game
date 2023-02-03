#include "Koopa.h"
#include "PlayScene.h"
#include "SuperMushroom.h"
CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	start_y = y;
	start_x = x;
	die_start = -1;
	waking_start = -1;
	SetState(KOOPA_STATE_WALKING);
	 mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_DIE || state == KOOPA_STATE_SLIDE)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
//	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;

		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
		if (dynamic_cast<CSuperMushroom*>(e->obj))
			OnCollisionWithSuperMushroom(e);
	
}
void CKoopa::OnCollisionWithSuperMushroom(LPCOLLISIONEVENT e)
{
	CSuperMushroom* supermushroom = dynamic_cast<CSuperMushroom*>(e->obj);
	// jump on top >> kill Goomba and deflect a bit 
	if (untouchable==0)
	{
		if (supermushroom->GetState() != SUPERMUSHROOM_STATE_WALKING)
		{
			supermushroom->SetState(SUPERMUSHROOM_STATE_WALKING);
		}
	} 
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);

	if ((state == KOOPA_STATE_DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	{
		SetState(KOOPA_STATE_WAKING);
		startWakingTime();
	}
	else if (state == KOOPA_STATE_WAKING && (GetTickCount64() - waking_start > KOOPA_WAKING_TIMEOUT)) {
		SetState(KOOPA_STATE_WALKING);
		waking_start = 0;
	}
	else if (state == KOOPA_STATE_SLIDE) {
		if (x_mario > x) {
			isRight = false;
		}
		else
			isRight = true;
		FindSlideDirection();
		if (vx == 0 && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT)) {
		
			SetState(KOOPA_STATE_WAKING);
			startWakingTime();
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{

	int aniId = -1;
	if (state == KOOPA_STATE_WALKING) {
		if (vx > 0) {
			aniId = ID_ANI_KOOPA_WALKING_RIGHT;
		}
		else
			aniId = ID_ANI_KOOPA_WALKING_LEFT;
	}
	if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_KOOPA_DIE;
	}
	if (state == KOOPA_STATE_WAKING) {
		aniId = ID_ANI_KOOPA_WAKING;
	}
	if (state == KOOPA_STATE_SLIDE) {
		aniId = ID_ANI_KOOPA_SLIDE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALKING:
		if (waking_start > 0) {
			y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
		}
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SLIDE:
			y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE)/2;
			ay = KOOPA_GRAVITY;
			vx = KOOPA_SLIDE_SPEED;
		break;
	}
}

void CKoopa::FindSlideDirection()
{
	if (isRight == true) {
		vx = KOOPA_SLIDE_SPEED;
	}
	else
		vx = - KOOPA_SLIDE_SPEED;
}
