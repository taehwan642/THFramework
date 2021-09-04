#include "DXUT.h"
#include "RenderManager.h"
#include "TileMapManager.h"
#include "Sprite.h"
#include "Minimap.h"

void Minimap::CreateTile()
{
	for (int i = 0; i < 50; ++i)
	{
		Sprite* sp = new Sprite;
		sp->isUI = true;
		minimapTile.push_back(sp);
		sp->scale = { minimapTileScale, minimapTileScale };
		sp->isactive = false;
	}
}

void Minimap::DeleteTile()
{
	for (auto& iter : minimapTile)
		delete iter;
	minimapTile.clear();
}

Minimap::Minimap() : minimapPos(250, 250)
{
	CreateTile();
}

Minimap::~Minimap()
{
	DeleteTile();
}

void Minimap::Update()
{
	for (auto& iter : minimapTile)
		iter->isactive = false;

	std::list<Object*>& objs = RenderManager::GetInstance().GetRenderObjects();
	for (auto& iter : objs)
	{
		if (false == iter->isactive)
			continue;
		for (auto& iter2 : minimapTile)
		{
			if (false == iter2->isactive)
			{
				Sprite* sp = static_cast<Sprite*>(iter2);
				bool isOn = false;
				if (nullptr != dynamic_cast<Player*>(iter))
				{
					sp->SetTexture(L"bluebox.png");
					isOn = true;
				}
				else if (nullptr != dynamic_cast<Monster*>(iter))
				{
					sp->SetTexture(L"redbox.png");
					isOn = true;
				}
				else if (nullptr != dynamic_cast<Block*>(iter))
				{
					sp->SetTexture(L"whitebox.png");
					isOn = true;
				}

				if (true == isOn)
				{
					iter2->isactive = true;
					iter2->position = ((iter->position / 4) * minimapTileScale) + minimapPos;
				}
				break;
			}
		}
	}
}
