#include "Fireball.h"
#include "PlayScene.h"

CFireball::CFireball(float x, float y)
{
	this->x = x;
	this->y = y;
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
	//x = vx * dt;
	//y = vy * dt;
	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);
	if (x_mario < x) {
		x -= FIRE_BALL_SPEED;
		if (y_mario > y) {
			y += FIRE_BALL_SPEED;
		}
		else if (y_mario < y) {
			y -=FIRE_BALL_SPEED;
		}
	}

	if (x_mario > x) {
		x += FIRE_BALL_SPEED;
		if (y_mario > y) {
			y += FIRE_BALL_SPEED;
		}
		else if (y_mario < y) {
			y -= FIRE_BALL_SPEED;
		}
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
