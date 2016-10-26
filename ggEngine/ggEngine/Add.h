#pragma once
#include "GGObject.h"
#include <string>
#include <list>
#include <d3d9.h>
#include "Text.h"
namespace ggEngine{
	class Tween;
	class TweenManager;
	class Font;
	class Sprite;
	class Group;
	class SpriteAnimation;
	class Cache;
	class DrawManager;
	class World;
	class Audio;
	class Add:public GGObject  {
	public:
		Add(World *world,Cache *Cache,TweenManager *tweenManager, DrawManager *drawManager, std::list<ggEngine::Group*> *groupList);
		Sprite* Sprite(double x, double y, std::string textureKey, Group *group);
		SpriteAnimation* SpriteAnimation(double x, double y, std::string textureKey ,int frameWidth, int frameHeight, Group *group, int defaultFrame = 0, int numberOfFrame = 0, int msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
		Group* Group();
		Text* Text(double x, double y, std::string fontKey , double width, double height, std::string text, Style style, ggEngine::Group *group);
		Audio* Audio(std::string audioKey);
		ggEngine::Tween* Tween(float &val, double end, double duration, std::function<double(int, double, double, int)> easingFunction);
		//ggEngine::Tween* Tween(double init, double end, double duration, std::function<void(double)> update, std::function<double(double)> easingFunction);

	private:
		TweenManager *tweenManager;
		Cache *cache;
		DrawManager *drawManager;
		LPDIRECT3DDEVICE9 device;
		World *world;
	};
}