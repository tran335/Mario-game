#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Game.h"


#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SLIDE_SPEED 1.0f

#define KOOPA_BBOX_WIDTH 51
#define KOOPA_BBOX_HEIGHT 79
#define KOOPA_BBOX_HEIGHT_DIE 51

#define KOOPA_DIE_TIMEOUT 5000
#define KOOPA_WAKING_TIMEOUT 2000

#define KOOPA_STATE_WALKING 801
#define KOOPA_STATE_DIE 802
#define KOOPA_STATE_WAKING 804
#define KOOPA_STATE_SLIDE 803

#define ID_ANI_KOOPA_WALKING_LEFT 801
#define ID_ANI_KOOPA_WALKING_RIGHT 805
#define ID_ANI_KOOPA_DIE 802
#define ID_ANI_KOOPA_WAKING 804
#define ID_ANI_KOOPA_SLIDE 803

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	CMario* mario;
	ULONGLONG die_start;
	ULONGLONG waking_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y);
	virtual void SetState(int state);
	void startWakingTime(){waking_start = GetTickCount64();}
};