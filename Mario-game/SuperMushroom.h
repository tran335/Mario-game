#pragma once
#include "GameObject.h"
#include "Mario.h"

#define SUPERMUSHROOM_GRAVITY 0.002f
#define SUPERMUSHROOM_WALKING_SPEED 0.05f


#define SUPERMUSHROOM_BBOX_WIDTH 48
#define SUPERMUSHROOM_BBOX_HEIGHT 48
#define SUPERMUSHROOM_BBOX_HEIGHT_DIE 7

#define SUPERMUSHROOM_DIE_TIMEOUT 500

#define SUPERMUSHROOM_STATE_WALKING 100
//#define SUPERMUSHROOM_STATE_DIE 200

#define ID_ANI_SUPERMUSHROOM_WALKING 510
//#define ID_ANI_SUPERMUSHROOM_DIE 5001

class CSuperMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	float start_y;


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithMario(LPCOLLISIONEVENT e);

public:
	CSuperMushroom(float x, float y);
	virtual void SetState(int state);
};