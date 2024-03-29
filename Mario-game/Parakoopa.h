#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Game.h"



#define PARAKOOPA_GRAVITY 0.001f
#define PARAKOOPA_WALKING_SPEED 0.02f
#define PARAKOOPA_JUMP_Y 0.4f
#define PARAKOOPA_SLIDE_SPEED 1.0f
#define BACK_TIME 3000

#define PARAKOOPA_BBOX_WIDTH 51
#define PARAKOOPA_BBOX_HEIGHT 79
#define PARAKOOPA_BBOX_HEIGHT_DIE 51

#define PARAKOOPA_DIE_TIMEOUT 5000
#define PARAKOOPA_WAKING_TIMEOUT 2000


#define PARAKOOPA_STATE_WALKING 900
#define PARAKOOPA_STATE_DIE 901
#define PARAKOOPA_STATE_WAKING 902
#define PARAKOOPA_STATE_SLIDE 903
#define PARAKOOPA_STATE_FLY 904

#define ID_ANI_PARAKOOPA_FLY_LEFT 7100
#define ID_ANI_PARAKOOPA_FLY_RIGHT 7101
#define ID_ANI_PARAKOOPA_WALKING_LEFT 7102
#define ID_ANI_PARAKOOPA_WALKING_RIGHT 7103
#define ID_ANI_PARAKOOPA_DIE 7104
#define ID_ANI_PARAKOOPA_WAKING 7106
#define ID_ANI_PARAKOOPA_SLIDE 7105

#define MARIO_SMALL_HANDLED_WIDTH 23
#define MARIO_SMALL_HANDLED_HEIGHT 2

#define MARIO_BIG_HANDLED_WIDTH 20
#define MARIO_BIG_HANDLED_HEIGHT 10

#define MARIO_RACCOON_HANDLED_WIDTH 35
#define MARIO_RACCOON_HANDLED_HEIGHT 10

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
	ULONGLONG reset_time;
	CMario* mario;
	ULONGLONG die_start;
	ULONGLONG waking_start;
	BOOLEAN isHandled;

	bool isBack = false;
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
	void OnCollisionWithCameraBound(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithBigBox(LPCOLLISIONEVENT e);


public:
	CParaKoopa(float x, float y);
	virtual void SetState(int state);
	void FindSlideDirection();
	void startWakingTime() { waking_start = GetTickCount64(); }
	int Getlevel() { return this->level; }
	void Setlevel(int level) { this->level = level; }
	void setPositionHandled();
	void HandledByMario() { isHandled = true; }
	void HandledByMarioRelease() { isHandled = false; }
	void startBack() { isBack = true; 	reset_time = GetTickCount64(); }
};
