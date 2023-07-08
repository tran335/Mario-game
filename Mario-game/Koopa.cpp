#include "Koopa.h"
#include "PlayScene.h"
#include "SuperMushroom.h"
#include "QuestionBrick.h"
CKoopa::CKoopa(float x, float y, int type) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	this->type = type;
	start_y = y;
	start_x = x;
	die_start = -1;
	waking_start = -1;
	isHandled = -1;
	SetState(KOOPA_STATE_WALKING);
	 mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}
LPGAME game = CGame::GetInstance();
void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_DIE || state == KOOPA_STATE_SLIDE)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{

		if (e->ny != 0)
		{
			vy = 0;
		}
		//else if (e->nx != 0)
		//{
		//	vx = -vx;
		//}
		if (dynamic_cast<CSuperMushroom*>(e->obj))
			OnCollisionWithSuperMushroom(e);
		else if (dynamic_cast<CQuestionBrick*>(e->obj))
			OnCollisionWithQuestionBrick(e);
		else if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		else if (dynamic_cast<CParaGoomba*>(e->obj))
			OnCollisionWithParaGoomba(e);
		else if (dynamic_cast<CKoopaBound*>(e->obj))
			OnCollisionWithKoopaBound(e);
		else if (dynamic_cast<CPlatform*>(e->obj))
			OnCollisionWithPlatform(e);
		//else if (dynamic_cast<CKoopa*>(e->obj))
		//	OnCollisionWithKoopa(e);
		//else if (dynamic_cast<CParaKoopa*>(e->obj))
		//	OnCollisionWithParaKoopa(e);
	
}
void CKoopa::OnCollisionWithSuperMushroom(LPCOLLISIONEVENT e)
{
	CSuperMushroom* supermushroom = dynamic_cast<CSuperMushroom*>(e->obj);
	if (untouchable == 0)
	{
		if (supermushroom->GetState() != SUPERMUSHROOM_STATE_WALKING || supermushroom->GetState() != LEAF_STATE_FLY)
		{
			if (mario->GetLevel() == MARIO_LEVEL_SMALL) 
				supermushroom->SetState(SUPERMUSHROOM_STATE_WALKING);
			else
				supermushroom->SetState(LEAF_STATE_FLY);
			/*StartUntouchable();*/
		}
	} 
}

void CKoopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionbrick = dynamic_cast<CQuestionBrick*>(e->obj);
	vx = -vx;
	if (untouchable == 0)
	{
		if (questionbrick->GetState() != QUESTIONBRICK_STATE_DISABLE)
		{
			questionbrick->SetState(QUESTIONBRICK_STATE_DISABLE);
		}
		
	}
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (e->nx!=0) {
		goomba->SetState(GOOMBA_STATE_DIE);
	}
	StartUntouchable();
}

void CKoopa::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* paragoomba = dynamic_cast<CParaGoomba*>(e->obj);
	if (e->nx != 0) {
		paragoomba->Setlevel(PARAGOOMBA_LEVEL_NO_WING);
		paragoomba->SetState(PARAGOOMBA_STATE_DIE);
	}
	StartUntouchable();

}


void CKoopa::OnCollisionWithKoopaBound(LPCOLLISIONEVENT e)
{
	if (e->nx != 0)
		{
			vx = -vx;
		}
}

void CKoopa::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	if (e->nx != 0) {
		vx = -vx;
	}
}

//void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
//{
//
//}
//
//void CKoopa::OnCollisionWithParaKoopa(LPCOLLISIONEVENT e)
//{
//
//}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	vy += ay * dt;
	vx += ax * dt;

	if (isHandled == true) {
		if (game->IsKeyDown(DIK_A)) {
			setPositionHandled();
		}
		else {
			HandledByMarioRelease();
			SetState(KOOPA_STATE_SLIDE);
		}
	}
	
	if ((state == KOOPA_STATE_DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT && isHandled != true))
	{
		SetState(KOOPA_STATE_WAKING);
		startWakingTime();
	}
	else if (state == KOOPA_STATE_WAKING && (GetTickCount64() - waking_start > KOOPA_WAKING_TIMEOUT)) {
		SetState(KOOPA_STATE_WALKING);
		waking_start = 0;
	}
	else if (state == KOOPA_STATE_SLIDE) {
		if (GetTickCount64() - die_start > KOOPA_RESET_TIMEOUT && isHandled != true) {
			SetState(KOOPA_STATE_WALKING);
			SetPosition(start_x, start_y);
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{

	int aniId = -1;
	if (type == RED_KOOPA) {
		if (state == KOOPA_STATE_WALKING) {
			if (vx > 0) {
				aniId = ID_ANI_KOOPA_WALKING_RIGHT;
			}
			else
				aniId = ID_ANI_KOOPA_WALKING_LEFT;
		}
		if (state == KOOPA_STATE_DIE)
		{
			aniId = ID_ANI_KOOPA_DIE;
		}
		if (state == KOOPA_STATE_WAKING) {
			aniId = ID_ANI_KOOPA_WAKING;
		}
		if (state == KOOPA_STATE_SLIDE) {
			aniId = ID_ANI_KOOPA_SLIDE;
		}
	}
	else if (type == GREEN_KOOPA) {
		if (state == KOOPA_STATE_WALKING) {
			if (vx > 0) {
				aniId = ID_ANI_GREEN_KOOPA_WALKING_RIGHT;
			}
			else
				aniId = ID_ANI_GREEN_KOOPA_WALKING_LEFT;
		}
		if (state == KOOPA_STATE_DIE)
		{
			aniId = ID_ANI_GREEN_KOOPA_DIE;
		}
		if (state == KOOPA_STATE_WAKING) {
			aniId = ID_ANI_GREEN_KOOPA_WAKING;
		}
		if (state == KOOPA_STATE_SLIDE) {
			aniId = ID_ANI_GREEN_KOOPA_SLIDE;
		}
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALKING:
		if (waking_start > 0) {
			y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
		}
		vx = KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SLIDE:
			//y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE)/2;
			ay = KOOPA_GRAVITY;
			/*if (nx == -1) {
				vx = -KOOPA_SLIDE_SPEED;
			}
			else if (nx == 1) {
				vx = KOOPA_SLIDE_SPEED;
			}*/
			setPositionSlide();
		break;
	}
}



void CKoopa::setPositionHandled()
{
	float x_mario, y_mario, vx_mario, vy_mario;
	mario->GetPosition(x_mario, y_mario); 
	mario->GetSpeed(vx_mario, vy_mario);

	if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
		if (vx_mario < 0)
			SetPosition(x_mario - MARIO_SMALL_HANDLED_WIDTH, y_mario - MARIO_SMALL_HANDLED_HEIGHT);
		else if (vx_mario > 0)
			SetPosition(x_mario + MARIO_SMALL_HANDLED_WIDTH, y_mario - MARIO_SMALL_HANDLED_HEIGHT);
	}
	else if (mario->GetLevel() == MARIO_LEVEL_BIG) {
		if (vx_mario < 0)
			SetPosition(x_mario - MARIO_BIG_HANDLED_WIDTH, y_mario + MARIO_BIG_HANDLED_HEIGHT);
		else if (vx_mario > 0)
			SetPosition(x_mario + MARIO_BIG_HANDLED_WIDTH, y_mario + MARIO_BIG_HANDLED_HEIGHT);
	}
	else {
		if (vx_mario < 0)
			SetPosition(x_mario - MARIO_RACCOON_HANDLED_WIDTH, y_mario + MARIO_RACCOON_HANDLED_HEIGHT);
		else if (vx_mario > 0)
			SetPosition(x_mario + MARIO_RACCOON_HANDLED_WIDTH, y_mario + MARIO_RACCOON_HANDLED_HEIGHT);
	}
}

void CKoopa::setPositionSlide()
{
	float x_mario, y_mario, vx_mario, vy_mario;
	mario->GetPosition(x_mario, y_mario);
	if (x < x_mario) 
		vx = -KOOPA_SLIDE_SPEED;
	else
		vx = KOOPA_SLIDE_SPEED;
}

