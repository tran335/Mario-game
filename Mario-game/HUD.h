#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Sprite.h"


#define ID_HUD 111112

#define HUD_CX 368
#define HUD_CY 610

class HUD : public CGameObject
{
protected:
	float x;
	float y;
	CMario* mario = NULL;
public:
	HUD(float x, float y);
	void Update();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0; t = 0; r = 0; b = 0; };
};

