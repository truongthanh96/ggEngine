#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "Helper.h"
#include "GGObject.h"
#include "Debug.h"

namespace ggEngine {
	class Texture : public GGObject {
	public:
		Texture(LPDIRECT3DDEVICE9 device, std::string fileSource, D3DCOLOR transcolor = NULL);
		Texture(LPDIRECT3DDEVICE9 device, int width, int height, D3DCOLOR transcolor = NULL);
		virtual ~Texture();
		int GetWidth();
		int GetHeight();
		LPDIRECT3DTEXTURE9 GetDxTexture() { return this->texture; }
		LPDIRECT3DSURFACE9 GetSurfaceTexture() { return this->textureSurface; }
		D3DXIMAGE_INFO GetInfo() { return this->info; }
	private:
		LPDIRECT3DTEXTURE9 texture;
		D3DXIMAGE_INFO info;
		LPDIRECT3DSURFACE9 textureSurface;
		int width;
		int height;
	};
}