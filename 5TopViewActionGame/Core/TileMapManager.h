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

// 이 클래스의 목적?
// 타일에 관련된 것들.
// 여기에서 플레이어를 생성할거냐
// 아니면 씬에서 플레이어를 생성하게 두고
// 플레이어의 위치를 넘겨줄건가.
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
	

	BlockType currentBlocktype;

	int mode = 0; // 0 = 타일맵, 1 = 오브젝트맵

public:
	float blockScale;
	Vec2 playerpos;

	TileMapManager();

	void Initialize();

	void UpdateManager();

	std::wstring GetTextureTag(BlockType type);

	[[nodiscard]] __forceinline std::vector<Block*>& GetBlockVector()
	{
		return tileBlocks;
	};

	void SaveBlocks(const std::string& mapTag);
	void SaveObject(const std::string& mapTag);
	void LoadBlocks(const std::string& mapTag);
	void LoadObject(const std::string& mapTag);

	void ChangeBlocks();

	void DeleteBlocks();
};