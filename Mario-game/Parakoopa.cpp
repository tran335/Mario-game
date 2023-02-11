#include "Parakoopa.h"
#include "PlayScene.h"
#include "SuperMushroom.h"
CParaKoopa::CParaKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PARAKOOPA_GRAVITY;
	this->type = type;
	start_y = y;
	start_x = x;
	die_start = -1;
	waking_start = -1;
	level = PARAKOOPA_LEVEL_WING;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CParaKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARAKOOPA_STATE_DIE || state == PARAKOOPA_STATE_SLIDE)
	{
		left = x - PARAKOOPA_BBOX_WIDTH / 2;
		top = y - PARAKOOPA_BBOX_HEIGHT_DIE / 2;
		right = left + PARAKOOPA_BBOX_WIDTH;
		bottom = top + PARAKOOPA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PARAKOOPA_BBOX_WIDTH / 2;
		top = y - PARAKOOPA_BBOX_HEIGHT / 2;
		right = left + PARAKOOPA_BBOX_WIDTH;
		bottom = top + PARAKOOPA_BBOX_HEIGHT;
	}
}

void CParaKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParaKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
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
void CParaKoopa::OnCollisionWithSuperMushroom(LPCOLLISIONEVENT e)
{
	CSuperMushroom* supermushroom = dynamic_cast<CSuperMushroom*>(e->obj);
	// jump on top >> kill Goomba and deflect a bit 
	if (untouchable == 0)
	{
		if (supermushroom->GetState() != SUPERMUSHROOM_STATE_WALKING)
		{
			supermushroom->SetState(SUPERMUSHROOM_STATE_WALKING);
		}
	}
}

void CParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);
	if (level == PARAKOOPA_LEVEL_WING) {
			SetState(PARAKOOPA_STATE_FLY);
	}

	if ((state == PARAKOOPA_STATE_DIE) && (GetTickCount64() - die_start > PARAKOOPA_DIE_TIMEOUT))
	{
		SetState(PARAKOOPA_STATE_WAKING);
		startWakingTime();
	}
	else if (state == PARAKOOPA_STATE_WAKING && (GetTickCount64() - waking_start > PARAKOOPA_WAKING_TIMEOUT)) {
		SetState(PARAKOOPA_STATE_WALKING);
		waking_start = 0;
	}
	else if (state == PARAKOOPA_STATE_SLIDE) {
		if (x_mario > x) {
			isRight = false;
		}
		else
			isRight = true;
		FindSlideDirection();
		if (vx == 0 && (GetTickCount64() - die_start > PARAKOOPA_DIE_TIMEOUT)) {

			SetState(PARAKOOPA_STATE_WAKING);
			startWakingTime();
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CParaKoopa::Render()
{

	int aniId = -1;


	if (level == PARAKOOPA_LEVEL_WING) {
		if (vx > 0)
			aniId = ID_ANI_PARAKOOPA_FLY_RIGHT;
		else
			aniId = ID_ANI_PARAKOOPA_FLY_LEFT;
	}
	else if (level == PARAKOOPA_LEVEL_NO_WING) {
		if (state == PARAKOOPA_STATE_DIE)
			aniId = ID_ANI_PARAKOOPA_DIE;
		else if (state == PARAKOOPA_STATE_SLIDE)
			aniId = ID_ANI_PARAKOOPA_SLIDE;
		else {
			if (vx > 0)
				aniId = ID_ANI_PARAKOOPA_WALKING_RIGHT;
			else
				aniId = ID_ANI_PARAKOOPA_WALKING_LEFT;
		}
			
	}

		/*if (state == PARAKOOPA_STATE_WALKING) {
			if (vx > 0) {
				aniId = ID_ANI_PARAKOOPA_WALKING_RIGHT;
			}
			else
				aniId = ID_ANI_PARAKOOPA_WALKING_LEFT;
		}
		if (state == PARAKOOPA_STATE_DIE)
		{
			aniId = ID_ANI_PARAKOOPA_DIE;
		}
		if (state == KOOPA_STATE_WAKING) {
			aniId = ID_ANI_PARAKOOPA_WAKING;
		}
		if (state == PARAKOOPA_STATE_SLIDE) {
			aniId = ID_ANI_PARAKOOPA_SLIDE;
		}*/
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CParaKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARAKOOPA_STATE_FLY:
	/*	vy = -PARAGOOMBA_JUMP_HIGH_SPEED;
		vx = -PARAGOOMBA_WALKING_SPEED;*/
		break;
	case PARAKOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (PARAKOOPA_BBOX_HEIGHT - PARAKOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARAKOOPA_STATE_WALKING:
		if (waking_start > 0) {
			y -= (PARAKOOPA_BBOX_HEIGHT - PARAKOOPA_BBOX_HEIGHT_DIE) / 2;
		}
		vx = -PARAKOOPA_WALKING_SPEED;
		break;
	case PARAKOOPA_STATE_SLIDE:
		y += (PARAKOOPA_BBOX_HEIGHT - PARAKOOPA_BBOX_HEIGHT_DIE) / 2;
		ay = PARAKOOPA_GRAVITY;
		vx = PARAKOOPA_SLIDE_SPEED;
		break;
	}
}

void CParaKoopa::FindSlideDirection()
{
	if (isRight == true) {
		vx = PARAKOOPA_SLIDE_SPEED;
	}
	else
		vx = -PARAKOOPA_SLIDE_SPEED;
}
