#include "DXUT.h"
#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	Renderer::GetInstance()->RemoveRenderTarget(this);
}

void Sprite::SetTexture(wstring path)
{
	texture = TextureManager::GetInstance()->LoadTexture(path);
	SetRect(&imageRect, 0, 0, texture->info.Width, texture->info.Height);
	Renderer::GetInstance()->AddRenderTarget(this);
}

RECT Sprite::GetRect()
{
	RECT r;
	r.right = position.x + (texture->info.Width / 2 * scale.x);
	r.left = position.x - (texture->info.Width / 2 * scale.x);
	r.top = position.y - (texture->info.Height / 2 * scale.y);
	r.bottom = position.y + (texture->info.Height / 2 * scale.y);
	return r;
}

bool Sprite::Animation(wstring path, float t, int f) // time, max frame
{
	deltatime += DELTATIME; // 0.0에서부터 시간이 계속 올라가요
	if (deltatime > t) // 매개변수로 받은 t보다 deltatime이 커지면, 다음 프레임으로 넘어가요
	{
		++frame; // 프레임 올려주고
		if (frame > f) // 현재 프레임이 최대 프레임보다 커졌으면
		{
			frame = 0; // 프레임 초기화
			return true; // 리턴
		}
		std::wstring p = path + L" (" + to_wstring(frame) + L").png"; // 이 부분이 중요하다
		// 자기 게임 리소스 속 애니메이션들을 나타내는,
		// player (1), player (2) 이런거나
		// player1, player2 이렇게 되어있으면
		// 따로 문자열을 세팅해줘야 잘 나온다.
		SetTexture(p); // 텍스쳐 세팅
		deltatime = 0; // 델타타임 초기화
	}
	return false;
}

void Sprite::Draw()
{
	if (isactive == false)
		return;
	if (texture == nullptr)
		return;
	isui ? Director::GetInstance()->sprite->Begin(D3DXSPRITE_ALPHABLEND) :
		Director::GetInstance()->sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	Director::GetInstance()->sprite->SetTransform(&GetMatrix());
	Vec3 center = { texture->info.Width * pivot.x, texture->info.Height * pivot.y, 0 };
	Director::GetInstance()->sprite->Draw(texture->texture, &imageRect, &center, nullptr, color);
	Director::GetInstance()->sprite->End();
}
