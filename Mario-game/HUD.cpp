#include "HUD.h"
#include "PlayScene.h"

HUD::HUD(float x, float y)
{
	this->x = x;
	this->y = y;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void HUD::Update()
{
	
}

void HUD::Render()
{
	
	CGame::GetInstance()->GetCamPos(x, y);
	
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_HUD)->Render(x+HUD_CX, y+HUD_CY);
}
