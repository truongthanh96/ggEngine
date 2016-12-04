#pragma once
#include <ggEngine.h>
#include "CharacterBase.h"
#include "CharacterConstant.h"
#include "InfoPanel.h"
using namespace ggEngine;
class CVGame;
class ItemBase;
class WeaponManager;
class WeaponWhip;
class Simon :public CharacterBase {
public:
	Simon(CVGame *cvGame, SpriteInfo *image, InfoPanel *infoPanel, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~Simon();
	void SetHealth(int heath);
	int GetHealth() { return this->health; }
	
	void SetMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
	int GetMaxHealth() { return this->maxHealth; }
	int GetHeartPoint() { return this->heartPoint; }

	void Attack() override;

	void Idle();
	void MoveLeft();
	void MoveRight();
	void Jump();
	void Kneel();
	void ClimbUp();
	void ClimbDown();
	void Hurt();
	void Death();
	void StandAttack();
	void KneelAttack();
	void ClimbDownAttack();
	void ClimbUpAttack();

	void LoseHealth(int health);
	void GainHealth(int health);
	void IncreaseScore(int score);
	void IncreaseState();
	void IncreaseHeartPoint(int point);
	void DecreaseHeartPoint(int point);
	void DescreasePPoint(int point);
	void SetShot(int shot, SpriteInfo *image);
	void UpgradeWhip();

	//void ThrowWeapon();

	void *HealthDown(int health) { this->health -= health; }

	InfoPanel *infoPanel = nullptr;
private:
	int health;
	int maxHealth;

	int score;
	
	int stagePoint;
	
	int heartPoint;
	
	int pPoint;
	
	int shot;

	int whipVersion;	// 1: standard, 2: short, 3: long

	bool isGrounding;	//for jump or for fall down or for hurt

	//bool isAllowManuallyControl;

	string incompleteAnim;
	WeaponManager *weaponManager = nullptr;
};