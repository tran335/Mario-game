#include "Fireball.h"
#include "PlayScene.h"
#include "BigBox.h"
#include "Platform.h"



void CFireball::OnNoCollision(DWORD dt)
{
	if (nx < 0) {
		x -= FIRE_BALL_SPEED;
		if (ny < 0)
			y += vy * dt;
		else
			y -= vy * dt;
	}
	if (nx > 0) {
		x += FIRE_BALL_SPEED;
		if (ny < 0)
			y -= vy * dt;
		else
			y += vy * dt;
	}
}

void CFireball::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBigBox*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatform(e);
	//if (dynamic_cast<CFireball*>(e->obj)) return;
	/*if (dynamic_cast<CMario*>(e->obj))
		OnCollisionWithMario(e);*/

}

void CFireball::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	CMario * mario = dynamic_cast<CMario*>(e->obj);
	if (untouchable == 0) {
		if (mario->GetLevel() > MARIO_LEVEL_BIG)
		{
			mario->SetLevel(MARIO_LEVEL_BIG);
			StartUntouchable();
		}
		else if (mario->GetLevel() > MARIO_LEVEL_SMALL)
		{
			mario->SetLevel(MARIO_LEVEL_SMALL);
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
		isCollision = true;
	}
}

void CFireball::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	isCollision = false;
}

CFireball::CFireball(float x, float y)
{
	this->x = x;
	this->y = y;
	ax = 0;
	unfindslidedirecttion_time = -1;
	unfindslidedirecttion = 1;
	ay = FIREBALL_GRAVITY;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CFireball::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int ani = ID_ANI_FIREBALL;
	animations->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}


void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	if (unfindslidedirecttion) {
		startfindslidedirecttion(dt);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireball::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALL_BBOX_WIDTH / 2;
	t = y - FIREBALL_BBOX_HEIGHT / 2;
	r = l + FIREBALL_BBOX_WIDTH;
	b = t + FIREBALL_BBOX_HEIGHT;
}

void CFireball::startfindslidedirecttion(DWORD dt)
{
	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);

	if (x_mario < x) {
		nx = -1;
		if (y_mario > y) {
			ny= -1;
		}
		else if (y_mario < y) {
			ny = 1;
		}
	}

	else if (x_mario > x) {
		nx = 1;
		if (y_mario > y) {
			ny=1;
		}
		else if (y_mario < y) {
			ny=-1;
		}
	}
	unfindslidedirecttion = 0;	
}
