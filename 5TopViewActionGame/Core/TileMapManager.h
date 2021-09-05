#pragma once
#include "Sprite.h"
#include "Singleton.h"

enum BlockType
{
	NONE,
	FLOOR,
	OBSTICLE
};

class Block final : 
	public Sprite
{
public:
	BlockType type;
	void Update() override {};
};

#define Row 6
#define Column 20

class TileMapManager final :
	public Singleton<TileMapManager>
{
private:
	// 현재 실제 게임에서 렌더링되고있는 블록
	std::vector<Block*> blocks;

	// 타일맵 찍을 때 렌더할 블록
	Block* blockss[Row][Column];
	
	float blockScale;

	BlockType currentBlocktype;

public:
	TileMapManager();

	void Initialize();

	void UpdateManager();

	[[nodiscard]] __forceinline std::vector<Block*>& GetBlockVector()
	{
		return blocks;
	};

	void SaveBlocks(const std::string& mapTag);
	void LoadBlocks(const std::string& mapTag);

	void ChangeBlocks();

	void DeleteBlocks();
};