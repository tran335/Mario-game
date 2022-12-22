#pragma once
#include "GameObject.h"

#define PARAGOOMBA_GRAVITY 0.002f
#define PARAGOOMBA_WALKING_SPEED 0.05f


#define PARAGOOMBA_BBOX_WIDTH 48
#define PARAGOOMBA_BBOX_HEIGHT 48
#define PARAGOOMBA_BBOX_HEIGHT_DIE 7

#define PARAGOOMBA_DIE_TIMEOUT 500

#define PARAGOOMBA_STATE_WALKING 100
#define PARAGOOMBA_STATE_DIE 200

#define ID_ANI_PARAGOOMBA_WALKING 6000
#define ID_ANI_PARAGOOMBA_DIE 6001

class CParaGoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CParaGoomba(float x, float y);
	virtual void SetState(int state);
};

