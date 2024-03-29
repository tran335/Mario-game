#include "Goomba.h"
#include "PlayScene.h"

CGoomba::CGoomba(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	start_y = y;
	start_x = x;
	isfinddropdirection = 0;
	SetState(GOOMBA_STATE_WALKING);
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	if (dynamic_cast<CCameraBound*>(e->obj))
		OnCollisionWithCameraBound(e);
	
}

void CGoomba::OnCollisionWithCameraBound(LPCOLLISIONEVENT e)
{
	CCameraBound* camerabound = dynamic_cast<CCameraBound*>(e->obj);
	if (e->ny < 0 && isBack==false)
	{
		isBack = true;
		reset_time = GetTickCount64();
		isCollision = false;
	}
}

void CGoomba::startfinddropdirecttion()
{
	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);

	if (x_mario < x) {
		nx = -1;
	}
	else if (x_mario > x) {
		nx = 1;
	}
	isfinddropdirection = 1;
}


void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	if (state == GOOMBA_STATE_KICK_BY_RACCOON && state == GOOMBA_STATE_KICK_BY_KOOPA) {
		if (isfinddropdirection) {
			startfinddropdirecttion();
		}
		else {
			if (nx == -1)
				vx = -GOOMBA_WALKING_VX;
			else
				vx = GOOMBA_WALKING_VX;
			isfinddropdirection = 0;
		}
	}

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}
	if (isBack) {
		if ((GetTickCount64() - reset_time) > BACK_TIME) {
			SetState(GOOMBA_STATE_WALKING);
			SetPosition(start_x, start_y);
			isBack = false;
			reset_time = 0;
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == ID_ANI_GOOMBA_WALKING) {
		aniId = ID_ANI_GOOMBA_WALKING;
	}
	else if (state == GOOMBA_STATE_KICK_BY_RACCOON || state == GOOMBA_STATE_KICK_BY_KOOPA) {
		aniId = ID_ANI_GOOMBA_DROP;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			isCollision = true;
			break;
		case GOOMBA_STATE_KICK_BY_RACCOON:
			vy = -GOOMBA_KICK_BY_RACCOON_SPEED;
			if (isfinddropdirection == 1) {
				if (nx == -1)
					vx = -GOOMBA_WALKING_VX;
				else
					vx = GOOMBA_WALKING_VX;
			}
			break;
		case GOOMBA_STATE_KICK_BY_KOOPA:
			vy = -GOOMBA_KICK_BY_KOOPA_SPEED;
			break;

	}
}
