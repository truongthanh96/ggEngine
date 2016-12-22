#include "BatEnemy.h"
#include "CVGame.h"
#include "Simon.h"
BatEnemy::BatEnemy(CVGame * cvGame, SpriteInfo * spriteInfo) : TweenEnemyBase(cvGame,spriteInfo,16,16,0,4,400)
{
	this->CreateAnimation("move", { 1,2,3,2 }, true);
	this->CreateAnimation("idle", 0, 0, false);
	SetMoveX(40);
	SetSpeed(0.5);
}

BatEnemy::~BatEnemy()
{
}

void BatEnemy::RunLeft()
{
	TweenEnemyBase::RunLeft();
	this->PlayAnimation("move");
	AddTween(true);
	this->isMoving = true;
}

void BatEnemy::RunRight()
{
	TweenEnemyBase::RunRight();
	this->PlayAnimation("move");
	AddTween(false);
	this->isMoving = true;
}

void BatEnemy::Update()
{
	if (!this->isMoving) {
		Vector simon = this->cvGame->simon->position;
		if (abs(simon.x - this->position.x) < this->simonDetectRange && abs(simon.y - this->position.y) < this->simonDetectRange) {
			if (simon.x > this->position.x) {
				RunRight();
			}
			else {
				RunLeft();
			}
		}
	}
}

void BatEnemy::AddTween(bool isLeft)
{
	Vector simon = this->cvGame->simon->position;
	Vector moveTo = simon;
	int modifier = 1;
	if (isLeft) modifier = -1;
	moveTo.x = this->position.x + modifier*moveX;
	this->cvGame->add->MoveTo(this, moveTo, round(moveX / speed) * DEFAULT_MS_PER_FRAME_FOR_ANIMATION, Easing::easeInQuad, Easing::easeOutQuad)->SetOnFinish([=]() {
		this->body->immoveable = false;
		this->body->velocity.x = modifier*speed;
	})->Start();
}