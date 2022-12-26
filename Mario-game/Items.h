#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define ITEMS_THROW_UP 2000
#define ITEMS_JUMP_SPEED_Y 2100

#define ITEM_WIDTH 48
#define ITEM_BBOX_WIDTH 48
#define ITEM_BBOX_HEIGHT 48

class CItems : public CGameObject {
public:
	CItems(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};