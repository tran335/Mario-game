#include "VenusFireTrap.h"
#include "PlayScene.h"

CVenusFireTrap::CVenusFireTrap(float x, float y)
{
	this->x = x;
	this->y = y;
	start_y = y;
	vy = -VENUS_SPEED;
	 mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy;
	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);
	

	if (isShooting == false) {
		if (y_mario > y)
			isUp = false;
		else if (y_mario < y)
			isUp = true;
		if (x_mario < y) {
			isRight = false;
		}
		else if(x_mario > y) {
			isRight = true;
		}
		if (y < start_y - VENUS_HEIGHT) // have not overlap with pipe
		{
			vy = 0.0f;
			StartShootTime();
		}
	}
	else if (GetTickCount64() - shootingStartTime > VENUS_SHOOTING_TIME) {
		shootingStartTime = 0;
		isShooting = false;
		createFireball = false;
		vy = VENUS_SPEED;
	}
	if (y > start_y + VENUS_HEIGHT) {
		vy = -VENUS_SPEED;
	}

	CGameObject::Update(dt, coObjects);
	
}

void CVenusFireTrap::Render()
{
	int aniId = 0;
	if (isRight == true) {
		if (isShooting == true) {
			if (isUp == true)
				aniId = ID_ANI_VENUS_SHOOT_UP_RIGHT;
			else
				aniId = ID_ANI_VENUS_SHOOT_DOWN_RIGHT;
		}
		else
			if (isUp == true) {
				aniId = ID_ANI_VENUS_UP_RIGHT;
			}
			else
				aniId = IC_ANI_VENUS_DOWN_RIGHT;
	}
	else 
	{
		if (isShooting == true) {
			if (isUp == true)
				aniId = ID_ANI_VENUS_SHOOT_UP_LEFT;
			else
				aniId = ID_ANI_VENUS_SHOOT_DOWN_LEFT;
		}
		else
			if (isUp == true) {
				aniId = ID_ANI_VENUS_UP_LEFT;
			}
			else
				aniId = IC_ANI_VENUS_DOWN_LEFT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	if (createFireball == true) {
		fireball = new CFireball(x, y);
		fireball->Render();
	}
	//RenderBoundingBox();
}



void CVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - VENUS_BBOX_WIDTH / 2;
	t = y - VENUS_BBOX_HEIGHT / 2;
	r = l + VENUS_BBOX_WIDTH;
	b = t + VENUS_BBOX_HEIGHT;
}

void CVenusFireTrap::StartShootTime()
{
	isShooting = true;
	shootingStartTime = GetTickCount64();
	createFireball = true;
}
