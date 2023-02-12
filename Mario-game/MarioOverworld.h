#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"
#include "Mario.h"

#define MARIO_WALKING_SPEED		0.3f

#define MARIO_GRAVITY			0.002f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_WALKING_UP	300
#define MARIO_STATE_WALKING_DOWN	400


#pragma region ANIMATION_ID

#define ID_ANI_MARIO 9990



#pragma endregion


#define MARIO_SMALL_BBOX_WIDTH  40
#define MARIO_SMALL_BBOX_HEIGHT 48

class CMarioOverworld : public CMario
{
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int untouchable;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	DWORD dt;

public:
	CMarioOverworld(float x, float y) : CMario(x, y)
	{
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;

	}


	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};