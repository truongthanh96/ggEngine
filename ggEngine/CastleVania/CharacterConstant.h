#pragma once
#include <string>
class CharacterConstant {
public:
	static constexpr const double SIMON_JUMP_FORCE = 3.5f; // 300.0f;
	static constexpr const double SIMON_MOVE_FORCE = 1.5f;// 200.0f;
	static constexpr const double SIMON_CLIMB_FORCE = 1.0f;// 200.0f;
	static constexpr const double SIMON_JUMP_TIME = 500;

	static constexpr const double SIMON_HURT_FORCE = 1.0f;
	static constexpr const double SIMON_HURT_TIME = 500;

	static constexpr const double SIMON_MAX_HEALTH = 16;


	static constexpr const int SIMON_FIRE_LONG_TIME = 2000;
	static constexpr const int SIMON_FIRE_SHORT_TIME = 500;

};