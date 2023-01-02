#pragma once
#include "GameObject.h"


#define VENUS_BBOX_WIDTH 48
#define VENUS_BBOX_HEIGHT 95
#define VENUS_HEIGHT 70
#define ID_ANI_VENUS_SHOOT_UP 603
#define ID_ANI_VENUS_SHOOT_DOWN 604
#define ID_ANI_VENUS_UP 602
#define IC_ANI_VENUS_DOWN 601
#define VENUS_SPEED 1.0f
#define VENUS_SHOOTING_TIME 2000


class CVenusFireTrap : public CGameObject
{
	bool isShooting = false;
	bool isUp = false;
	float width;
	float height;
	float start_y;
	ULONGLONG shootingStartTime = 0;
public:
	CVenusFireTrap(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void StartShootTime();
};

