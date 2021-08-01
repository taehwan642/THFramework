#include "DXUT.h"
#include "RenderManager.h"
#include "Minimap.h"

void Minimap::CreateMinimapTile()
{
	// �����.
}

void Minimap::DeleteMinimapTile()
{
	// �����Ѵ�.
}

// 1. ���� �������ǰ��ִ� Ÿ��, �÷��̾� �� ������Ʈ���� ��� �޾ƿ´�.
// 2. �޾ƿ���, ������Ʈ�� �̴ϸ� Ÿ���� �ϳ� �����.
// 3. �̴ϸ� Ÿ���� ��ġ�� ������ �߽� ��ġ + ������Ʈ�� ��ġ / ������ �̴ϸ� ũ�� �� �ϸ� �ǰڴ�.
// 4. �� ��ȸ������, �������� �̴ϸ��� ������ �� �ְ� �־��ش�.

void Minimap::Update()
{
	DeleteMinimapTile();
	renderingSprites = RenderManager::GetInstance().GetRenderObjects();
	
	CreateMinimapTile();
}
