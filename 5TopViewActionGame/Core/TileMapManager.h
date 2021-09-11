#pragma once
#include "Sprite.h"
#include "Singleton.h"

enum BlockType
{
	NONE,
	FLOOR, // ��
	WALL, // ��
	PLAYER // ������Ʈ
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

	// ���� ���� ���ӿ��� �������ǰ��ִ� ���
	std::vector<Block*> tileBlocks;
	std::vector<Block*> objBlocks; // ������Ʈ

	// Ÿ�ϸ� ���� �� ������ ���
	Block* blocks[Row][Column];
	Block* objects[Row][Column];
	
	float blockScale;

	BlockType currentBlocktype;

	int mode = 0; // 0 = Ÿ�ϸ�, 1 = ������Ʈ��

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