#include "DXUT.h"
#include "RenderManager.h"
#include "TileMapManager.h"
#include "Sprite.h"
#include "Minimap.h"

void Minimap::CreateMinimapTile()
{
	renderingSprites = RenderManager::GetInstance().GetRenderObjects();
	for (auto& iter : renderingSprites)
	{
		if (false == iter->isactive)
			continue;

		Sprite* sp = new Sprite;
		sp->isUI = true;

		float minimapTileScale = 0.5f;

		sp->scale = { minimapTileScale, minimapTileScale };

		if (nullptr != dynamic_cast<Player*>(iter))
			sp->SetTexture(L"bluebox.png");
		else if (nullptr != dynamic_cast<Monster*>(iter))
			sp->SetTexture(L"redbox.png");
		else if(nullptr != dynamic_cast<Block*>(iter)) 
			sp->SetTexture(L"whitebox.png");
			
		Vec2 minimapTilePosition = (iter->position / 4) * minimapTileScale;
		sp->position = minimapPosition + minimapTilePosition;
		
		minimap.push_back(sp);
	}
}

void Minimap::DeleteMinimapTile()
{
	for (int i = 0; i < std::size(minimap); ++i)
	{
		delete minimap[i];
	}
	minimap.clear();
}

void Minimap::Update()
{
	DeleteMinimapTile();
	CreateMinimapTile();
}
