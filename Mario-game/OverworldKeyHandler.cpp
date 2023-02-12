#include "OverworldKeyHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void COverworldKeyHandler::OnKeyDown(int KeyCode)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_1:
		CGame::GetInstance()->InitiateSwitchScene(INTRO_SCENE);
		break;
	case DIK_2:
		CGame::GetInstance()->InitiateSwitchScene(OVERWORLD_SCENE);
		break;
	case DIK_3:
		CGame::GetInstance()->InitiateSwitchScene(WORLD_MAP_1_1_SCENE);
		break;
	}
}

void COverworldKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//switch (KeyCode)
	//{
	//case DIK_S:
	//	mario->SetState(MARIO_STATE_RELEASE_JUMP);
	//	break;
	//case DIK_DOWN:
	//	mario->SetState(MARIO_STATE_SIT_RELEASE);
	//	break;
	//case DIK_A:
	//	mario->SetState(MARIO_STATE_SPIN_RELEASE);
	//	break;
	//case DIK_4:
	//	CGame::GetInstance()->InitiateSwitchScene(1);
	//	break;
	//case DIK_5:
	//	CGame::GetInstance()->InitiateSwitchScene(2);
	//	break;
	//case DIK_6:
	//	CGame::GetInstance()->InitiateSwitchScene(3);
	//	break;
	//}
}

void COverworldKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
			mario->SetState(MARIO_STATE_WALKING_RIGHT);

	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}
