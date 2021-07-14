#include "DXUT.h"
#include "Texture.h"
#include "AniSprite.h"

AniSprite::AniSprite() :
	currentAnimationTag(L""),
	currentFrame(0),
	currentTick(0.f)
{
}

void 
AniSprite::CreateAnimation(const std::wstring& tag, int frameCount, float tickTime)
{
	std::pair<float, std::vector<Texture*>> p;
	
	p.first = tickTime;
	for (int i = 0; i < frameCount; ++i)
	{
		const auto& route = tag + L" (" + std::to_wstring(i + 1) + L").png";
		Texture* tex = TextureManager::GetInstance().LoadTexture(route);
		p.second.push_back(tex);
	}

	animationMap.emplace(tag, p);
}

bool 
AniSprite::PlayAnimation(const std::wstring& tag)
{
	if (currentAnimationTag != tag)
	{
		currentAnimationTag = tag;
		currentAnimation = animationMap[tag];
		currentTick = 0;
		currentFrame = 1;
		SetTexture(currentAnimation.second[0]);
	}

	currentTick += DXUTGetElapsedTime();

	if (currentTick > currentAnimation.first)
	{
		++currentFrame;
		if (currentFrame > currentAnimation.second.size())
		{
			currentFrame = 0;
			return true;
		}
		SetTexture(currentAnimation.second[currentFrame - 1]);
		currentTick = 0;
	}
	return false;
}
