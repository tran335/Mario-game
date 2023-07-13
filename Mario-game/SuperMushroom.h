#pragma once
#include "GameObject.h"
#include "Mario.h"

#define SUPERMUSHROOM_GRAVITY 0.001f
#define LEAF_GRAVITY_AX 0.004f
#define LEAF_GRAVITY_AY 0.002f
#define SUPERMUSHROOM_WALKING_SPEED 0.05f


#define SUPERMUSHROOM_BBOX_WIDTH 48
#define SUPERMUSHROOM_BBOX_HEIGHT 48

#define MAX_Y 150

#define DIRECT_TIME 1000

#define SUPERMUSHROOM_BBOX_HEIGHT_DIE 7

#define SUPERMUSHROOM_DIE_TIMEOUT 500

#define SUPERMUSHROOM_STATE_WALKING 100
#define LEAF_STATE_FLY 200

#define ID_ANI_SUPERMUSHROOM_WALKING 510
#define ID_ANI_LEAF 520
#define ID_ANI_LEAF_RIGHT 530
//#define ID_ANI_SUPERMUSHROOM_DIE 5001

class CSuperMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	float start_y;
	CMario* mario;
	BOOLEAN isDirect = false;
	BOOLEAN isCollision = true;
	BOOLEAN isRight = false;
	float direct_time;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return (isCollision != false && state !=LEAF_STATE_FLY); };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMario(LPCOLLISIONEVENT e);

public:
	CSuperMushroom(float x, float y);
	virtual void SetState(int state);
	void startDirect() { direct_time = GetTickCount64(); isDirect = true; };
};