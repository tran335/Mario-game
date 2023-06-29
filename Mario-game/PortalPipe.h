#pragma once

#include "GameObject.h"
#include "Mario.h"

#define PORTAL_TYPE_INPUT 1
#define PORTAL_TYPE_OUTPUT 2

#define PORTAL_NAME_IN 3
#define PORTAL_NAME_OUT 4

#define PORTAL_BBOX_WIDTH 48
#define PORTAL_BBOX_HEIGHT 48

class CPortalPipe : public CGameObject
{
	int type;	
	int name;
	CMario* mario;
	float x;
	float y;
	float width;
	float height;
public:
	CPortalPipe(float l, float t, float r, float b, int name, int type);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetType() { return type; }
	int GetName() { return name; }
};
