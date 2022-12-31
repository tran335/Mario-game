#pragma once
#include "GameObject.h"

#define VENUS_BBOX_WIDTH 48
#define VENUS_BBOX_HEIGHT 95
#define ID_ANI_VENUS_SHOOT_UP 603
#define ID_ANI_VENUS_SHOOT_DOWN 604
#define ID_ANI_VENUS_UP 602
#define IC_ANI_VENUS_DOWN 601



class CVenusFireTrap : public CGameObject
{
	bool isShooting = false;
	bool isUp = false;
	float width;
	float height;
public:
	CVenusFireTrap(float width, float height);
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

