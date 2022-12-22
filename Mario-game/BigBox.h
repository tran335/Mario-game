#pragma once
#include "GameObject.h"

#define BIGBOX_BBOX_WIDTH 48
#define BIGBOX_BBOX_HEIGHT 48

class CBigBox : public CGameObject
{
protected:
	float width;
	float height;

public:

	CBigBox(float width, float height);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

