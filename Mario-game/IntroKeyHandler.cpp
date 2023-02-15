#include "IntroKeyHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "MarioOverworld.h"
#include "PlayScene.h"

void CIntroKeyHandler::OnKeyDown(int KeyCode)
{
	CMarioOverworld* mario = (CMarioOverworld*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

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
	case DIK_S:
		CGame::GetInstance()->InitiateSwitchScene(OVERWORLD_SCENE);
		break;
	}
}

void CIntroKeyHandler::OnKeyUp(int KeyCode)
{
	CMarioOverworld* mario = (CMarioOverworld*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CIntroKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMarioOverworld* mario = (CMarioOverworld*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

