#pragma once
#include "GameObject.h"

#define KOOPABOUND_BBOX_WIDTH 24
#define KOOPABOUND_BBOX_HEIGHT 96

class CKoopaBound : public CGameObject
{
protected:
	float width;
	float height;

public:

	CKoopaBound(float width, float height);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

