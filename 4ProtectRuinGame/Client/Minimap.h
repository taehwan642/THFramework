#pragma once

struct MinimapTile
{
	
};

class Minimap
{
private:
	std::vector<Object*> minimap;

	void CreateMinimapTile();

	void DeleteMinimapTile();

public:
	std::list<Object*> renderingSprites;

	void Update();
};

