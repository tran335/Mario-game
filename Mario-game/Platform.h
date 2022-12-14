#pragma once

#define PLATFORM_BBOX_WIDTH 48
#define PLATFORM_BBOX_HEIGHT 48

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected: 
	float width;
	float height;

public: 

	CPlatform(float width, float height);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};

typedef CPlatform* LPPLATFORM;