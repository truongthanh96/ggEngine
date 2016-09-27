#pragma once
#include "GGObject.h"
#include "IGetGroup.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include <list>
namespace ggEngine{
	class Map;
	class Group;
	class Add;
	class Preload;
	class DrawManager;
	class Game;
	class State : public GGObject, public IGetGroup{
	public:
		State(Game *game);
		~State();
		void Start();
		Add *add;
		Preload *preload;
		virtual void Destroy();
		std::list<Group*> GetGroupList() { return this->groupList; }
		virtual void Init() = 0; //Called after start a State
		virtual void Preload() = 0; //Called after init
		virtual void Create() = 0;//Called after preload complete
		virtual void Update() = 0;//Called after each game update loop
		virtual void PreRender() = 0;//Called before enter each render
		virtual void Render() = 0;//Called after render completed
		virtual void Pause() = 0;//Called when the game is set to paused
		virtual void Resume() = 0;//Called when the game is resumed
		virtual void ShutDown() = 0;//Called when start a new State
	protected:
		Game *game;
	private:
		std::list<Group*> groupList;
		DrawManager *drawManager;
		Map *map;
	};
}