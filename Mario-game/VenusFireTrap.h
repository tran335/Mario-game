#pragma once
#include "GameObject.h"
#include "Fireball.h"
#include "Mario.h"


#define VENUS_BBOX_WIDTH 48
#define VENUS_BBOX_HEIGHT 95
#define VENUS_HEIGHT 70

#define IC_ANI_VENUS_DOWN_LEFT 601
#define ID_ANI_VENUS_UP_LEFT 602
#define ID_ANI_VENUS_SHOOT_DOWN_LEFT 603
#define ID_ANI_VENUS_SHOOT_UP_LEFT 604

#define IC_ANI_VENUS_DOWN_RIGHT 605
#define ID_ANI_VENUS_UP_RIGHT 606
#define ID_ANI_VENUS_SHOOT_DOWN_RIGHT 607
#define ID_ANI_VENUS_SHOOT_UP_RIGHT 608

#define VENUS_SPEED 2.0f
#define VENUS_SHOOTING_TIME 2000


class CVenusFireTrap : public CGameObject
{
	friend class CFireball;
	bool isShooting = false;
	bool isUp = false;
	bool isRight = false;
	float width;
	float height;
	float start_y;
	ULONGLONG shootingStartTime = 0;
	CFireball* fireball;
	bool createFireball = false;
	CMario* mario = NULL;

public:
	CVenusFireTrap(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void StartShootTime();
};

