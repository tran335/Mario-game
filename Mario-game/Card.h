#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_CARD 44000

#define	CARD_WIDTH 48
#define CARD_BBOX_WIDTH 48
#define CARD_BBOX_HEIGHT 48

class CCard : public CGameObject {
public:
	CCard(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};
