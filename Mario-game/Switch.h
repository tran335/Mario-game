#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "SuperMushroom.h"

#define ID_ANI_SWITCH 7700

#define ID_ANI_SWITCH_DIE 7701
#define SWITCH_JUMP_Y		10.0f


#define SWITCH_STATE_DIE 1100
#define SWITCH_STATE_JUMP 1200
#define SWITCH_WIDTH 48
#define SWITCH_BBOX_HEIGHT_DIE 20
#define SWITCH_BBOX_WIDTH 48
#define SWITCH_BBOX_HEIGHT 48

class CSwitch : public CGameObject {
	float start_y;
	float jumpTime;


public:
	CSwitch(float x, float y);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void BrickStartToThrow() { jumpTime = GetTickCount64(); };
	virtual void SetState(int state);

};
