#include "HUD.h"
#include "PlayScene.h"

void HUD::Update()
{
	
}

void HUD::Render()
{
	
	//mario->GetPosition(x, y);

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_HUD)->Render(HUD_CX, HUD_CY);
}
