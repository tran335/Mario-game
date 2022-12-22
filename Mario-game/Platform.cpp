#include "Platform.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CPlatform::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - 24 + rect.right / 2;
	float yy = y - 24 + rect.bottom / 2;


	CGame::GetInstance()->Draw(xx, yy, bbox, nullptr, BBOX_ALPHA, rect.right-1, rect.bottom-1);
}

CPlatform::CPlatform(float width, float height)
{
		this->width = width;
		this->height = height;
}

void CPlatform::Render()
{
	RenderBoundingBox();
}

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 24;
	t = y - 24;
	r = l + width;
	b = t + height; 
}