#pragma once
#include "GameObject.h"

#define BOUND_BBOX_WIDTH 48
#define BOUND_BBOX_HEIGHT 48

class COverworldBound : public CGameObject
{
protected:
	float width;
	float height;

public:

	COverworldBound(float width, float height);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

