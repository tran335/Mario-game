#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	LPGAME game = CGame::GetInstance();
	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
			mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		CGame::GetInstance()->InitiateSwitchScene(INTRO_SCENE);
		break;
	case DIK_2:
		CGame::GetInstance()->InitiateSwitchScene(OVERWORLD_SCENE);
		break;
	case DIK_3:
		CGame::GetInstance()->InitiateSwitchScene(WORLD_MAP_1_1_SCENE);
		break;
	case DIK_4:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_5:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_6:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_SPIN);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CKoopa* koopa = (CKoopa*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene());
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_SPIN_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			if (game->IsKeyDown(DIK_S) && mario->GetLevel() == MARIO_LEVEL_RACCOON) {
				mario->SetState(MARIO_STATE_FLY);
			}
				else
					mario->SetState(MARIO_STATE_RUNNING_RIGHT);
				
		}
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
	if (game->IsKeyDown(DIK_A))
	{
		if (game->IsKeyDown(DIK_S) && mario->GetLevel() == MARIO_LEVEL_RACCOON) {
			mario->SetState(MARIO_STATE_FLY);
		}
		else
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
	else
		mario->SetState(MARIO_STATE_IDLE);
}