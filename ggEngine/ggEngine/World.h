#pragma once
#include "Group.h"
namespace ggEngine{
	class Game;
	class World : public Group{
	public:
		World(Game *game);
		virtual ~World();
		void Reset();
		void UpdateWorldPosition() override;
	};
}