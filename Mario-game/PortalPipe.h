#pragma once

#include "GameObject.h"

#define PORTAL_TYPE_INPUT 1
#define PORTAL_TYPE_OUTPUT 2

class CPortalPipe : public CGameObject
{
	int type;	

	float x;
	float y;
	float width;
	float height;
public:
	CPortalPipe(float l, float t, float r, float b, int type);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetType() { return type; }
};
