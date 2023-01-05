#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_FIREBALL 620
#define FIREBALL_BBOX_WIDTH 25
#define FIREBALL_BBOX_HEIGHT 25
#define FIRE_BALL_SPEED 0.5f

class CFireball : public CGameObject
{

public:
	CFireball(float x, float y);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

