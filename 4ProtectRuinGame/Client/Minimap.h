#pragma once

class Minimap
{
private:
	std::vector<Object*> minimap;

	void CreateMinimapTile();

	void DeleteMinimapTile();

	Vec2 minimapPosition;

public:
	__forceinline Minimap();

	__forceinline ~Minimap();

	std::list<Object*> renderingSprites;

	void Update();
};

Minimap::Minimap() :
	minimapPosition(0, 0)
{
	
}

Minimap::~Minimap()
{
	for (auto& iter : minimap)
	{
		delete iter;
	}
}