#pragma once
#include "GameObject.h"

class CCameraBound : public CGameObject
{
protected:
	float width;
	float height;

public:

	CCameraBound(float width, float height);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

