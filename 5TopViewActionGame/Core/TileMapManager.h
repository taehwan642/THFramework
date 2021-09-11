#pragma once
#include "Sprite.h"
#include "Singleton.h"

enum BlockType
{
	NONE,
	FLOOR, // 맵
	WALL, // 맵
	PLAYER // 오브젝트
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
	std::vector<BlockType> walls;

	// 현재 실제 게임에서 렌더링되고있는 블록
	std::vector<Block*> tileBlocks;
	std::vector<Block*> objBlocks; // 오브젝트

	// 타일맵 찍을 때 렌더할 블록
	Block* blocks[Row][Column];
	Block* objects[Row][Column];
	
	float blockScale;

	BlockType currentBlocktype;

	int mode = 0; // 0 = 타일맵, 1 = 오브젝트맵

public:
	TileMapManager();

	void Initialize();

	void UpdateManager();

	std::wstring GetTextureTag(BlockType type);

	[[nodiscard]] __forceinline std::vector<Block*>& GetBlockVector()
	{
		return tileBlocks;
	};

	void SaveBlocks(const std::string& mapTag);
	void LoadBlocks(const std::string& mapTag);

	void ChangeBlocks();

	void DeleteBlocks();
};