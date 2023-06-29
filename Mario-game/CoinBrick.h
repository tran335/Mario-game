#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"



#define ID_ANI_COINBRICK 8000
#define COINBRICK_JUMP_SPEED_Y		190.0f
#define CONINBRICK_RETURN_START_POS_VY 20.0f

#define JUMP_TIME 300

#define COINBRICK_STATE_THROW_UP 1100
#define COINBRICK_STATE_NORMAL 1200
#define COINBRICK_WIDTH 48
#define COINBRICK_BBOX_WIDTH 36
#define COINBRICK_BBOX_HEIGHT 48

class CCoinBrick : public CGameObject {
	float start_y;
	float jumpTime = 0;
	virtual int IsBlocking() { return 0; }

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CCoinBrick();
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void BrickStartToThrow() { jumpTime = GetTickCount64(); };
	virtual void SetState(int state);
};