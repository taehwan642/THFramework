#pragma once

class Minimap
{
public:
	std::vector<Object*> minimapTile;

	void CreateTile();
	void DeleteTile();

	Vec2 minimapPos;
	float minimapTileScale = 0.5f;

	Minimap();
	~Minimap();

	void Update();
};