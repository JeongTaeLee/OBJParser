#pragma once
#include "singleton.h"

struct texture
{
	LPDIRECT3DTEXTURE9 lpTex;
	D3DXIMAGE_INFO info;

	texture(LPDIRECT3DTEXTURE9 _lpTex, D3DXIMAGE_INFO _info)
		:lpTex(_lpTex), info(_info)
	{
	}
	~texture()
	{
		SAFE_RELEASE(lpTex);
	}
};

class ImageManager :
	public singleton<ImageManager>
{
private:
	map<string, texture*> textures;
public:
	ImageManager();
	virtual ~ImageManager();

	texture* GetTexture(const string & key, const string & path);
};

#define IMAGE ImageManager::GetInst()

#define GIMG(key, path) IMAGE.GetTexture(key, path)
