#include "Items.h"

void CItems::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);
	//RenderBoundingBox();
}

void CItems::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ITEM_BBOX_WIDTH / 2;
	t = y - ITEM_BBOX_HEIGHT / 2;
	r = l + ITEM_BBOX_WIDTH;
	b = t + ITEM_BBOX_HEIGHT;
}
void CItems::SetState(int state)
{

	CGameObject::SetState(state);
	switch (state)
	{
	case ITEMS_THROW_UP:
		vx = 0;
		//vy = 0;
		vy = - ITEMS_JUMP_SPEED_Y;

		break;
	}
}