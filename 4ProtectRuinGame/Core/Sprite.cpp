#include "DXUT.h"
#include "Sprite.h"

LPD3DXSPRITE Sprite::sprite = nullptr;

void Sprite::Render()
{
	if (isactive == false)
		return;

	if (texture == nullptr)
		return;

	DWORD flag;
	flag = (isUI == true ? D3DXSPRITE_ALPHABLEND : D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Begin(flag);
	sprite->SetTransform(&GetMatrix());
	Vec3 center = {
		texture->info.Width * pivot.x,
		texture->info.Height * pivot.y,
		0 };
	sprite->Draw(texture->texture, &imgRect, &center, nullptr, color);
	sprite->End();
}

