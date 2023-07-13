#pragma once
#include "Animation.h"
#include "Animations.h"
#include "Game.h"
#include "GameObject.h"
#include "Mario.h"


#define ID_HUD 111112

#define HUD_CX 368
#define HUD_CY 1310

class HUD
{
protected:
	float x;
	float y;
	CMario* mario = NULL;
public:
	void Update();
	void Render();
};

