#include "Fireball.h"
#include "PlayScene.h"

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
	if (unfindslidedirecttion) {
		startfindslidedirecttion(dt);
	}
	if (nx < 0) {
		x -= FIRE_BALL_SPEED;
		if(ny<0)
			y += FIRE_BALL_SPEED;
		else
			y -= FIRE_BALL_SPEED;
	}
	if (nx > 0) {
		x += FIRE_BALL_SPEED;
		if (ny < 0)
			y -= FIRE_BALL_SPEED;
		else
			y += FIRE_BALL_SPEED;
	}

	CGameObject::Update(dt, coObjects);
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
