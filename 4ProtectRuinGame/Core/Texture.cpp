#include "DXUT.h"
#include "Texture.h"

Texture* TextureManager::LoadTexture(const std::wstring& path)
{
	for (auto& iter : texturelist)
		if (iter->tag == path)
			return iter;

	Texture* tex = new Texture();
	const auto& route = L"Resources/" + path;
	tex->tag = path;

	if (FAILED(D3DXCreateTextureFromFileEx(
		DXUTGetD3D9Device(),
		route.c_str(),
		-2, -2, 1, 0,
		D3DFORMAT::D3DFMT_A8B8G8R8,
		D3DPOOL::D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE, 0,
		&tex->info, nullptr, &tex->texture)))
	{
		std::wcout << "FAILED : " << route << std::endl;
		delete tex;
		return nullptr;
	}
	else
	{
		std::wcout << "COMPLETE : " << route << std::endl;
		texturelist.emplace_back(tex);
		return tex;
	}
}

void TextureManager::ReleaseAllTexture()
{
	for (auto& iter : texturelist)
	{
		iter->texture->Release();
		delete iter;
	}
	texturelist.clear();
}
