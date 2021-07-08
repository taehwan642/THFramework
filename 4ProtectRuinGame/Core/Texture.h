#pragma once
#include "Singleton.h"

struct Texture
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;
	std::wstring tag;
};

class TextureManager final :
    public Singleton<TextureManager>
{
private:
	std::list<Texture*> texturelist;

public:
	__forceinline Texture* LoadTexture(const std::wstring& path);
	void ReleaseAllTexture();
};

