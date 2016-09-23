#pragma once
#include "GGObject.h"
#include <map>
#include <string>
#include <d3d9.h>
namespace ggEngine {
	class Texture;
	class Game;
	class Cache:public GGObject {
	public:
		Cache(Game* game);
		~Cache();
		void Destroy();
		void ClearAll();
		bool CreateTexture(std::string textureKey, std::string textureName);
		Texture* GetTexture(std::string textureKey);
	private:
		std::map<std::string, Texture*> textureMap;
		Game *game;
		LPDIRECT3DDEVICE9 device;
	};
}