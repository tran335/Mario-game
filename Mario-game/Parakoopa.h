#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Game.h"



#define PARAKOOPA_GRAVITY 0.001f
#define PARAKOOPA_WALKING_SPEED 0.05f
#define PARAKOOPA_SLIDE_SPEED 1.0f

#define PARAKOOPA_BBOX_WIDTH 51
#define PARAKOOPA_BBOX_HEIGHT 79
#define PARAKOOPA_BBOX_HEIGHT_DIE 51

#define PARAKOOPA_DIE_TIMEOUT 5000
#define PARAKOOPA_WAKING_TIMEOUT 2000

#define PARAKOOPA_STATE_WALKING 801
#define PARAKOOPA_STATE_DIE 802
#define PARAKOOPA_STATE_WAKING 804
#define PARAKOOPA_STATE_SLIDE 803

#define ID_ANI_PARAKOOPA_WALKING_LEFT 801
#define ID_ANI_PARAKOOPA_WALKING_RIGHT 805
#define ID_ANI_PARAKOOPA_DIE 802
#define ID_ANI_PARAKOOPA_WAKING 804
#define ID_ANI_PARAKOOPA_SLIDE 803

#define ID_ANI_GREEN_PARAKOOPA_WALKING_LEFT 806
#define ID_ANI_GREEN_PARAKOOPA_WALKING_RIGHT 807
#define ID_ANI_GREEN_PARAKOOPA_DIE 808
#define ID_ANI_GREEN_PARAKOOPA_WAKING 809
#define ID_ANI_GREEN_PARAKOOPA_SLIDE 810

#define PARAKOOPA_LEVEL_WING 1
#define PARAKOOPA_LEVEL_NO_WING 2


class CParaKoopa : public CGameObject
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
	bool isRight = true;
	int untouchable = 0;

	int level;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithSuperMushroom(LPCOLLISIONEVENT e);

public:
	CParaKoopa(float x, float y);
	virtual void SetState(int state);
	void FindSlideDirection();
	void startWakingTime() { waking_start = GetTickCount64(); }
	int Getlevel() { return this->level; }
	void Setlevel(int level) { this->level = level; };
};