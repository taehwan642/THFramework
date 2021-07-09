#include "DXUT.h"
#include "RenderManager.h"
#include "Texture.h"
#include "Sprite.h"

void Sprite::Render()
{
	if (isactive == false)
		return;

	if (texture == nullptr)
		return;

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&GetMatrix());
	Vec3 center = {
		texture->info.Width * pivot.x, 
		texture->info.Height * pivot.y, 
		0 };
	sprite->Draw(texture->texture, &GetRect(), &center, nullptr, color);
	sprite->End();
}
