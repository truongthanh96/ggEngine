#pragma once
#include "WalkingEnemyBase.h"
class EnemySkillBase;
class Boss3 : public WalkingEnemyBase {
public:
	Boss3(CVGame *cvGame, SpriteInfo* image, bool isPrimaryBoss);
	~Boss3();

	void Update() override;
private:
	void Fire(bool isLeft, Vector position);
	void SetBullet(EnemySkillBase * bullet);
	EnemySkillBase* bullet = nullptr;
	int fireInterval;
	Timer fireTimer;
	bool isPrimaryBoss;
};