#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTIONBRICK 7000

#define ID_ANI_QUESTIONBRICK_DISABLE 7001
#define QUESTIONBRICK_JUMP_Y		10.0f
#define BRICK_RETURN_START_POS_VY 2.0f

#define JUMP_TIME 200

#define QUESTIONBRICK_STATE_DISABLE 1100
#define QUESTIONBRICK_STATE_NORMAL 1200
#define QUESTIONBRICK_WIDTH 48
#define QUESTIONBRICK_BBOX_WIDTH 48
#define QUESTIONBRICK_BBOX_HEIGHT 48

class CQuestionBrick : public CGameObject {
	float start_y;
	float jumpTime;
    
	
public:
	CQuestionBrick(float x, float y);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void BrickStartToThrow() { jumpTime = GetTickCount64(); };
	virtual void SetState(int state);
	
};