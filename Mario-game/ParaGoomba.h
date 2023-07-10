#pragma once
#include "GameObject.h"
#include "debug.h"
#include "CameraBound.h"

#define PARAGOOMBA_GRAVITY 0.002f
#define PARAGOOMBA_WALKING_SPEED 0.1f


#define PARAGOOMBA_BBOX_WIDTH 48
#define PARAGOOMBA_BBOX_HEIGHT 48
#define PARAGOOMBA_BBOX_HEIGHT_DIE 28

#define PARAGOOMBA_DIE_TIMEOUT 500

#define PARAGOOMBA_STATE_WING 100
#define PARAGOOMBA_STATE_DIE 200
#define PARAGOOMBA_STATE_NORMAL 300
#define PARAGOOMBA_STATE_FLY 400

#define PARAGOOMBA_LEVEL_WING 1
#define PARAGOOMBA_LEVEL_NO_WING 2


#define ID_ANI_PARAGOOMBA_WING 6000
#define ID_ANI_PARAGOOMBA_DIE 6001
#define ID_ANI_PARAGOOMBA_NORMAL 6002
#define ID_ANI_PARAGOOMBA_FLY 6003
#define ID_ANI_PARAGOOMBA_DROP 6004

#define PARAGOOMBA_FLY_TIMES 4
#define PARAGOOMBA_WALK_TIME 3000


#define PARAGOOMBA_JUMP_HIGH_SPEED 0.5f
#define PARAGOOMBA_JUMP_LOW_SPEED 0.3f

#define BACK_TIME 2000
class CParaGoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	float die_start;
	BOOLEAN isOnPlatform;
	BOOLEAN isBack = false;
	int jumpTime;
	float walkingTime;
	float reset_time;
	float start_x;
	float start_y;

	int level;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithCameraBound(LPCOLLISIONEVENT e);

public:
	CParaGoomba(float x, float y);
	virtual void SetState(int state);
	void StartWalkingTime() { walkingTime = GetTickCount64(); };
	int Getlevel() { return this->level; }
	void Setlevel(int level) {  this->level=level ; };
};

