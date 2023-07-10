#pragma once
#include "GameObject.h"
#include "CameraBound.h"
#include "Mario.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.07f
#define GOOMBA_KICK_BY_RACCOON_SPEED 0.8f
#define GOOMBA_KICK_BY_KOOPA_SPEED 0.6f
#define BACK_TIME 2000

#define GOOMBA_BBOX_WIDTH 48
#define GOOMBA_BBOX_HEIGHT 48
#define GOOMBA_BBOX_HEIGHT_DIE 30

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_KICK_BY_RACCOON 300
#define GOOMBA_STATE_KICK_BY_KOOPA 400

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_DROP 5002

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 

	float start_x;
	float start_y;
	float reset_time;
	CMario* mario = NULL;

	ULONGLONG die_start;
	BOOLEAN isBack = false;
	BOOLEAN isfinddropdirection;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return (state != GOOMBA_STATE_KICK_BY_RACCOON && state != GOOMBA_STATE_KICK_BY_KOOPA); };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithCameraBound(LPCOLLISIONEVENT e);
	void startfinddropdirecttion();

public: 	
	CGoomba(float x, float y);
	virtual void SetState(int state);
};