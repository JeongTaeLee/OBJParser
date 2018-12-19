#include "DXUT.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
	for (auto Iter : textures)
		SAFE_DELETE(Iter.second);

	textures.clear();
}

texture * ImageManager::GetTexture(const string & key, const string & path)
{
	auto find = textures.find(key);

	if (find != textures.end())
		return find->second;

	LPDIRECT3DTEXTURE9 d3dTex;
	D3DXIMAGE_INFO info;

	if (FAILED(D3DXCreateTextureFromFileExA(g_device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &d3dTex)))
	{
		DEBUG_LOG("이미지 로드 실패 : " << key << " / " << path);
		return nullptr;
	}

	return textures.insert(make_pair(key, new texture(d3dTex, info))).first->second;
}
