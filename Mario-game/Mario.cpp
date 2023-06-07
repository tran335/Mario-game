#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "ParaGoomba.h"
#include "Coin.h"
#include "Portal.h"
#include "BigBox.h"
#include "CameraBound.h"
#include "QuestionBrick.h"
#include "CoinBrick.h"
#include "KoopaBound.h"
#include "Koopa.h"
#include "SuperMushroom.h"
#include "VenusFireTrap.h"
#include "Fireball.h"
#include "Piranha.h"
#include "Parakoopa.h"
#include "PlayScene.h"
#include "Switch.h"
#include "Card.h"
#include "Platform.h"


#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	LPGAME game = CGame::GetInstance();
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (isOutIn == true) {
		SetPosition(6911, 1491);
		isOutIn = false;
	}
	if (isOutOut == true) {
		SetPosition(6917, 1054);
		isOutOut = false;
	}
	
	if ((isDie==true) && (GetTickCount64() - die_start > MARIO_DIE_TIMEOUT))
	{
		isDie = false;
		CGame::GetInstance()->InitiateSwitchScene(OVERWORLD_SCENE);
	}
	if (GetTickCount64() - spin_time > MARIO_SPIN_TIME and spin_time>0)
	{
		spin_time = 0;
		isSpining = false;
	}
	isOnPlatform = false;
	if (state != MARIO_STATE_PRE_FLY) {
		if (isRunning == true)
		{
			power++;

			if (power > MARIO_RUNNING_TIME) {
				SetState(MARIO_STATE_PRE_FLY);
			}
		}
	}
	else {
		if (power > MARIO_RUNNING_TIME) {
			SetState(MARIO_STATE_FLY);
			power--;
		}
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (e->ny < 0) isOnPlatform = true;

	if (e->ny < 0) {
		isOnPlatform = true;
		vy = 0;
	}
	else if (e->nx!=0)
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CParaGoomba*>(e->obj))
		OnCollisionWithParaGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBigBox*>(e->obj))
		OnCollisionWithBigBox(e);
	else if (dynamic_cast<CCameraBound*>(e->obj))
		OnCollisionWithCameraBound(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CKoopaBound*>(e->obj))
		OnCollisionWithKoopaBound(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CCoinBrick*>(e->obj))
		OnCollisionWithCoinBrick(e);
	else if (dynamic_cast<CSuperMushroom*>(e->obj))
		OnCollisionWithSuperMushroom(e);
	else if (dynamic_cast<CVenusFireTrap*>(e->obj))
		OnCollisionWithVenusFireTrap(e);
	else if (dynamic_cast<CPiranha*>(e->obj))
		OnCollisionWithPiranha(e);
	else if (dynamic_cast<CFireball*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CParaKoopa*>(e->obj))
		OnCollisionWithParaKoopa(e);
	else if (dynamic_cast<CSwitch*>(e->obj))
		OnCollisionWithSwitch(e);
	else if (dynamic_cast<CCard*>(e->obj))
		OnCollisionWithCard(e);
	else if (dynamic_cast<CPortalPipe*>(e->obj))
		OnCollisionWithPortalPipe(e);

}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			
				if (goomba->GetState() != GOOMBA_STATE_DIE)
				{
					if (level == MARIO_LEVEL_RACCOON)
					{
						if (isSpining==true) 
						{
							if (goomba->GetState() != GOOMBA_STATE_DIE)
							{
								goomba->SetState(GOOMBA_STATE_DIE);
							}
						}
						else
						{
							level = MARIO_LEVEL_BIG;
							StartUntouchable();
						}
					}
					else if (level > MARIO_LEVEL_SMALL)
					{
						level = MARIO_LEVEL_SMALL;
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);
					}
				}
			
		}
	}
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionbrick = dynamic_cast<CQuestionBrick*>(e->obj);
	if(e->ny>0)
	{

			if (questionbrick->GetState() != QUESTIONBRICK_STATE_DISABLE)
			{
				questionbrick->SetState(QUESTIONBRICK_STATE_DISABLE);
				isHitting = true;
				
			}
			vy = 0;	
	}
}

void CMario::OnCollisionWithCoinBrick(LPCOLLISIONEVENT e)
{
	CCoinBrick* coinbrick = dynamic_cast<CCoinBrick*>(e->obj);

		if (e->ny > 0)
		{
				if (coinbrick->GetState() != COINBRICK_STATE_THROW_UP && isHitting==true)
				{
					coinbrick->SetState(COINBRICK_STATE_THROW_UP);
					isHitting = false;
				}
		}
}

void CMario::OnCollisionWithSuperMushroom(LPCOLLISIONEVENT e)
{
	CSuperMushroom* supermushroom = dynamic_cast<CSuperMushroom*>(e->obj);

		if (e->ny > 0)
		{
			if (supermushroom->GetState() != SUPERMUSHROOM_STATE_WALKING && supermushroom->GetState() != LEAF_STATE_FLY && isHitting==true)
			{
				if (level == MARIO_LEVEL_SMALL)
					supermushroom->SetState(SUPERMUSHROOM_STATE_WALKING);
				else
					supermushroom->SetState(LEAF_STATE_FLY);
				isHitting = false;
			}
		}
		else
		{
			if (untouchable == 0 && (supermushroom->GetState() == SUPERMUSHROOM_STATE_WALKING || supermushroom->GetState() == LEAF_STATE_FLY))
			{
				if (supermushroom->GetState() == LEAF_STATE_FLY)
					SetLevel(MARIO_LEVEL_RACCOON);
				else {
					SetLevel(MARIO_LEVEL_BIG);
				}

				e->obj->Delete();
				StartUntouchable();
			}
	}
}

void CMario::OnCollisionWithCameraBound(LPCOLLISIONEVENT e)
{
	CCameraBound * camerabound  = dynamic_cast<CCameraBound*>(e->obj);

	if (e->ny < 0)
	{
		SetState(MARIO_STATE_DIE);
	}
}

void CMario::OnCollisionWithSwitch(LPCOLLISIONEVENT e)
{
	CSwitch* cswitch = dynamic_cast<CSwitch*>(e->obj);

	if (e->nx < 0)
	{
		cswitch->SetState(SWITCH_STATE_JUMP);
	}
}

void CMario::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* paragoomba = dynamic_cast<CParaGoomba*>(e->obj);
	if (e->ny < 0)
	{
		if (paragoomba->GetState() != PARAGOOMBA_STATE_DIE) {
			if (paragoomba->Getlevel() != PARAGOOMBA_LEVEL_NO_WING)
			{
				paragoomba->Setlevel(PARAGOOMBA_LEVEL_NO_WING);
				StartUntouchable();
			}
			else {
				paragoomba->SetState(PARAGOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		
	}
	else 
	{
		if (untouchable == 0)
		{
			if (paragoomba->GetState() != PARAGOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithParaKoopa(LPCOLLISIONEVENT e)
{
	CParaKoopa* parakoopa = dynamic_cast<CParaKoopa*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (parakoopa->Getlevel() != PARAKOOPA_LEVEL_NO_WING)
		{
			parakoopa->Setlevel(PARAKOOPA_LEVEL_NO_WING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else {
			parakoopa->SetState(PARAKOOPA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (parakoopa->GetState() != PARAKOOPA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					SetState(MARIO_STATE_DIE);
				}
			}
			else
			{
				SetState(MARIO_STATE_KICK);
				parakoopa->SetState(PARAKOOPA_STATE_SLIDE);
				isKicking = false;
			}
		}
	}
}

void CMario::OnCollisionWithBigBox(LPCOLLISIONEVENT e)
{

}

void CMario::OnCollisionWithKoopaBound(LPCOLLISIONEVENT e)
{
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	LPGAME game = CGame::GetInstance();

	if (e->ny < 0)
	{
		if (koopa->GetState() != KOOPA_STATE_DIE)
		{
			koopa->SetState(KOOPA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else 
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() != KOOPA_STATE_DIE && koopa->GetState()!=KOOPA_STATE_SLIDE)
			{
				if (level == MARIO_LEVEL_RACCOON)
				{
					if (isSpining == true)
					{
						if (koopa->GetState() != KOOPA_STATE_DIE)
						{
							koopa->SetState(KOOPA_STATE_DIE);
						}
					}
					else
					{
						level = MARIO_LEVEL_BIG;
						StartUntouchable();
					}
				}
				else if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}

			else {
					if (game->IsKeyDown(DIK_A) && (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))) {
						koopa->HandledByMario();
						isPickup = true;
					}
					else {
						isPickup = false;
						SetState(MARIO_STATE_KICK);
						koopa->SetState(KOOPA_STATE_SLIDE);
						isKicking = false;
					}
			}
		}

	}
}

void CMario::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
	CVenusFireTrap* venus = dynamic_cast<CVenusFireTrap*>(e->obj);

		if (untouchable == 0)
		{
			
			if (level > MARIO_LEVEL_BIG)
			{
				level = MARIO_LEVEL_BIG;
				StartUntouchable();
			}
			else if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
}

void CMario::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	CPiranha* venus = dynamic_cast<CPiranha*>(e->obj);

	if (untouchable == 0)
	{

		if (level > MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level > MARIO_LEVEL_SMALL)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			//DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	CFireball* fireball = dynamic_cast<CFireball*>(e->obj);

	if (untouchable == 0)
	{
		e->obj->Delete();
		if (level > MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level > MARIO_LEVEL_SMALL)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithCard(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
	
}

void CMario::OnCollisionWithPortalPipe(LPCOLLISIONEVENT e)
{
	CPortalPipe* pp = dynamic_cast<CPortalPipe*>(e->obj);
	if (e->ny < 0) {
		isOutIn = true;
	}
	else if (e->ny > 0) {
		isOutOut = true;
	}
}



//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isPickup) 
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X) 
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_PICK_UP_SHELL_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_PICK_UP_SHELL_LEFT;
				
			}
			else
			{
				aniId = ID_ANI_MARIO_SMALL_FRONT_PICK_UP_SHELL;
			}
		}
		else 
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (isKicking) 
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
		}
		else
			if (vx == 0)
			{
				if(isPickup)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_PICK_UP_SHELL_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_PICK_UP_SHELL_LEFT;
				}
				else 
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (isPickup) 
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_FRONT_PICK_UP_SHELL;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_RIGHT;
				}
				else
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (isPickup)
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_FRONT_PICK_UP_SHELL;
					else if (ax == - MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_LEFT;
					else if (ax == - MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_LEFT;
				}
				else
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_PRE_FLY_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_PRE_FLY_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else if (isKicking)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_KICK_LEFT;
		}
		else if(isSpin) 
		{
			if (isRunning)
			{
				 if (isPrefly)
				{
					 if (isFly)
					 {
						 if (nx >= 0)
						 {
							 aniId = ID_ANI_MARIO_RACCOON_FLY_RIGHT;
						 }
						 else
							 aniId = ID_ANI_MARIO_RACCOON_FLY_LEFT;
					 }
					 else
					 {
						 if (nx >= 0)
						 {
							 aniId = ID_ANI_MARIO_RACCOON_PRE_FLY_RIGHT;
						 }
						 else
							 aniId = ID_ANI_MARIO_RACCOON_PRE_FLY_LEFT;
					 }
				}
				else 
				 {
					 if (nx >= 0)
					 {
						 aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
					 }
					 else
						 aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				 }
			}
			
			else 
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_SPIN_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_SPIN_LEFT;
			}
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}
	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (isKicking) 
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_KICK_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		startRunning();
		isRunning = true;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		startRunning();
		isRunning = true;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;

			else
				vy = -MARIO_JUMP_SPEED_Y;

		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DIE_SPEED;
		ax = 0.0f;
		vx = 0.0f;
		startDie();
		break;
	case MARIO_STATE_KICK:
		isKicking = true;
		state = MARIO_STATE_IDLE;
		break;
	case MARIO_STATE_SPIN:
		isSpin = true;
		isSpining = true;
		startIsSpin();
		break;
	case MARIO_STATE_SPIN_RELEASE:
		isSpin = false;
		break;
	case MARIO_STATE_PRE_FLY:
		running_time = 0;
		startPreFly();
		isPrefly = true;
		break;
	case MARIO_STATE_FLY:
		isFly = true;
		vy = -MARIO_JUMP_RUN_SPEED_Y;
		break;
	}


	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACCOON) 
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACCOON_BBOX_WIDTH / 2;
			top = y - MARIO_RACCOON_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_BBOX_WIDTH;
			bottom = top + MARIO_RACCOON_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	switch (l)
	{
	case MARIO_LEVEL_SMALL:
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
		level = l;
		break;
	case MARIO_LEVEL_BIG:
		y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;
		level = l;
		break;
	case MARIO_LEVEL_RACCOON:
		y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT;
		level = l;
		break;
	}
}

