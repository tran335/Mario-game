#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Game.h"



#define KOOPA_GRAVITY 0.001f
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

#define ID_ANI_KOOPA_WALKING_LEFT 811
#define ID_ANI_KOOPA_WALKING_RIGHT 805
#define ID_ANI_KOOPA_DIE 802
#define ID_ANI_KOOPA_WAKING 804
#define ID_ANI_KOOPA_SLIDE 803

#define ID_ANI_GREEN_KOOPA_WALKING_LEFT 806
#define ID_ANI_GREEN_KOOPA_WALKING_RIGHT 807
#define ID_ANI_GREEN_KOOPA_DIE 808
#define ID_ANI_GREEN_KOOPA_WAKING 809
#define ID_ANI_GREEN_KOOPA_SLIDE 810

#define RED_KOOPA 1
#define GREEN_KOOPA 2

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	int type;
	float start_x;
	float start_y;
	CMario* mario;
	ULONGLONG die_start;
	ULONGLONG waking_start;
	bool isRight=true;
	int untouchable = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithSuperMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y, int type);
	virtual void SetState(int state);
	void FindSlideDirection();
	void startWakingTime(){waking_start = GetTickCount64();}
};