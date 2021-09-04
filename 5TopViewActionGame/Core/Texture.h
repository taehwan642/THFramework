#pragma once
#include "Singleton.h"

struct Texture final
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
	[[nodiscard]] Texture* 
		LoadTexture(const std::wstring& path);

	__forceinline void 
		ReleaseAllTexture() 
	{
		for (auto& iter : texturelist)
		{
			iter->texture->Release();
			delete iter;
		}
		texturelist.clear();
	};
};

