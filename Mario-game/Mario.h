#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.4f
#define MARIO_RUNNING_SPEED		0.7f

#define MARIO_ACCEL_WALK_X	0.0006f
#define MARIO_ACCEL_RUN_X	0.0009f

#define MAX_Y 90



#define MARIO_JUMP_SPEED_Y		1.0f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_FLY_SPEED_Y	3.0f

#define MARIO_JUMP_RUN_SPEED_X 1.0f
#define MARIO_JUMP_SPEED_X		1.4f

#define MARIO_JUMP_DIE_SPEED 1.0f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.6f




#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500
#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define MARIO_STATE_KICK			800
#define MARIO_STATE_FLY			700
#define MARIO_STATE_PRE_FLY		900
#define MARIO_STATE_SPIN	1000
#define MARIO_STATE_DROP	1100
#define MARIO_STATE_SPIN_RELEASE 1200

#define MARIO_STATE_SWITCH_SCENE 1300

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_KICK_RIGHT 1101
#define ID_ANI_MARIO_KICK_LEFT 1110

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_IDLE_PICK_UP_SHELL_LEFT 12000
#define ID_ANI_MARIO_IDLE_PICK_UP_SHELL_RIGHT 12010

#define ID_ANI_MARIO_WALK_PICK_UP_SHELL_LEFT 13000
#define ID_ANI_MARIO_WALK_PICK_UP_SHELL_RIGHT 13010

#define ID_ANI_MARIO_JUMP_PICK_UP_SHELL_LEFT 14000
#define ID_ANI_MARIO_JUMP_PICK_UP_SHELL_RIGHT 14010

#define ID_ANI_MARIO_FRONT_PICK_UP_SHELL 15000

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

//#define ID_ANI_MARIO_FLY_RIGHT 1700
//#define ID_ANI_MARIO_FLY_LEFT 1701

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1701
#define ID_ANI_MARIO_SMALL_KICK_LEFT 1700

#define ID_ANI_MARIO_SMALL_IDLE_PICK_UP_SHELL_LEFT 18000
#define ID_ANI_MARIO_SMALL_IDLE_PICK_UP_SHELL_RIGHT 18010

#define ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_LEFT 19000
#define ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_RIGHT 19010

#define ID_ANI_MARIO_SMALL_JUMP_PICK_UP_SHELL_LEFT 20000
#define ID_ANI_MARIO_SMALL_JUMP_PICK_UP_SHELL_RIGHT 20010

#define ID_ANI_MARIO_SMALL_FRONT_PICK_UP_SHELL 21000

//RACCOON MARIO
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 1160
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 160

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 1161
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 161

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 1162
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 162

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 1164
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 164

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 1163
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 163

#define ID_ANI_MARIO_RACCOON_PRE_FLY_RIGHT 1167
#define ID_ANI_MARIO_RACCOON_PRE_FLY_LEFT 167

#define ID_ANI_MARIO_RACCOON_FLY_RIGHT 1166
#define ID_ANI_MARIO_RACCOON_FLY_LEFT 166

#define ID_ANI_MARIO_RACCOON_KICK_RIGHT 1170
#define ID_ANI_MARIO_RACCOON_KICK_LEFT 170

#define ID_ANI_MARIO_RACCOON_DROP_RIGHT 1165
#define ID_ANI_MARIO_RACCOON_DROP_LEFT 165

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 1168
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 168

#define ID_ANI_MARIO_RACCOON_SPIN_RIGHT 1169
#define ID_ANI_MARIO_RACCOON_SPIN_LEFT 169

#define ID_ANI_MARIO_RACCOON_IDLE_PICK_UP_SHELL_LEFT 1710
#define ID_ANI_MARIO_RACCOON_IDLE_PICK_UP_SHELL_RIGHT 11710

#define ID_ANI_MARIO_RACCOON_WALK_PICK_UP_SHELL_LEFT 1720
#define ID_ANI_MARIO_RACCOON_WALK_PICK_UP_SHELL_RIGHT 11720

#define ID_ANI_MARIO_RACCOON_JUMP_PICK_UP_SHELL_LEFT 1730
#define ID_ANI_MARIO_RACCOON_JUMP_PICK_UP_SHELL_RIGHT 11730

#define ID_ANI_MARIO_RACCOON_FRONT_PICK_UP_SHELL 1740

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON	3

#define MARIO_BIG_BBOX_WIDTH  42
#define MARIO_BIG_BBOX_HEIGHT 81
#define MARIO_BIG_SITTING_BBOX_WIDTH  43
#define MARIO_BIG_SITTING_BBOX_HEIGHT 55
#define MARIO_RACCOON_BBOX_WIDTH  65
#define MARIO_RACCOON_BBOX_HEIGHT 86

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  40
#define MARIO_SMALL_BBOX_HEIGHT 48


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_SPIN_TIME 1000
#define MARIO_RUNNING_TIME 10
#define MARIO_PRE_FLY_TIME 20
#define  MARIO_DIE_TIMEOUT 2000

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isKicking;
	BOOLEAN isSpin;
	BOOLEAN isSpining;
	BOOLEAN isRunning;
	BOOLEAN isPrefly;
	BOOLEAN isFly;
	BOOLEAN isDie;
	BOOLEAN isOutIn;
	BOOLEAN isOutOut;
	BOOLEAN isHitting;
	BOOLEAN isPickup;
	BOOLEAN isCollision;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float power;

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG spin_time;
	ULONGLONG pre_fly_time;
	ULONGLONG running_time;
	ULONGLONG die_start;
	BOOLEAN isOnPlatform;
	DWORD dt;
	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBigBox(LPCOLLISIONEVENT e);
	void OnCollisionWithCameraBound(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithParaKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithCoinBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithSuperMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranha(LPCOLLISIONEVENT e);
	void OnCollisionWithSwitch(LPCOLLISIONEVENT e);
	void OnCollisionWithCard(LPCOLLISIONEVENT e);
	void OnCollisionWithPortalPipe(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopaBound(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		isKicking = false;
		isSpin = false;
		isSpining = false;
		isRunning = false;
		isPrefly = false;
		isFly = false;
		isDie = false;
		isOutIn = false;
		isOutOut = false;
		isHitting = false;
		isPickup = false;
		power = 0;
		isCollision = 1;

		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		pre_fly_time = -1;
		running_time = -1;
		die_start = -1;
		isOnPlatform = false;
		coin = 0;


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

	void SetLevel(int l);
	int GetLevel() { return level; }
	int GetPower() { return power; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void startIsSpin() { spin_time = GetTickCount64(); }
	void startRunning() { running_time = GetTickCount64();}
	void startPreFly() { pre_fly_time = GetTickCount64();}
	void startDie() { isDie = true; die_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};