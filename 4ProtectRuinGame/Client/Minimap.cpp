#include "DXUT.h"
#include "RenderManager.h"
#include "Minimap.h"

void Minimap::CreateMinimapTile()
{
	// 만든다.
}

void Minimap::DeleteMinimapTile()
{
	// 삭제한다.
}

// 1. 현재 렌더링되고있는 타일, 플레이어 등 오브젝트들을 모두 받아온다.
// 2. 받아오고, 오브젝트당 미니맵 타일을 하나 만든다.
// 3. 미니맵 타일의 위치는 임의의 중심 위치 + 오브젝트의 위치 / 임의의 미니맵 크기 로 하면 되겠다.
// 4. 다 순회했으면, 렌더러에 미니맵을 렌더할 수 있게 넣어준다.

void Minimap::Update()
{
	DeleteMinimapTile();
	renderingSprites = RenderManager::GetInstance().GetRenderObjects();
	
	CreateMinimapTile();
}
