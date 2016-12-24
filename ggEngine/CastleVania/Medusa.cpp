#include "Medusa.h"
#include "CVGame.h"
#include "Simon.h"
#include "CVMap.h"
#include "CVBlock.h"
Medusa::Medusa(CVGame * cvGame, SpriteInfo * image) : ShootingEnemyBase(cvGame,image,32,32,0,4,200)
{
	this->body->SetActive(false);
	this->CreateAnimation("move", 0, 3, true);
	this->SetVisible(false);
	this->allowToDetectSimon = true;
	this->fireInterval = 1000;
	this->simonDetectRange = 500;
	moveY = 30;
	moveX = 0.05;
	moveSpeed = 1;
	this->isAwake = false;
}

Medusa::~Medusa()
{
	if (this->currentTween != nullptr) {
		this->currentTween->Stop();
	}
}

void Medusa::Update()
{
	EnemyBase::Update();
	if (!this->isAwake) return;
	if (this->moveTimer.stopwatch(this->moveInterval)) {
		this->lastSimonPosition = this->simon->position;
	}

	if (this->isMoving) {
		double x = this->position.x - this->startPosition.x;
		double increaseY = this->moveY*(sin(x*moveX));
		this->position.y = this->startPosition.y + increaseY;
	}
	else {
		int randomMin = Helper::GetRamdomIntNumber(randomMinX, randomMaxX);
		bool distance = this->position.x - this->lastSimonPosition.x;
		bool isSimonLeft = distance > 0;
		if (abs(distance) < randomMin) {
			if (isSimonLeft) {
				this->lastSimonPosition.x = this->position.x - randomMin;
			}
			else {
				this->lastSimonPosition.x = this->position.x + randomMin;
			}
		}
		auto block = this->simon->currentMap->GetCurrentBlock();
		if (this->lastSimonPosition.x < block->left) {
			this->lastSimonPosition.x = block->left;
		}
		else {
			if (this->lastSimonPosition.x > block->right) {
				this->lastSimonPosition.x = block->right;
			}
		}

		MoveTo(this->lastSimonPosition);
	}
}

void Medusa::Active()
{
	this->SetAlive(true);
	this->isMoving = false;
	this->isAwake = false;
	this->simon = this->cvGame->simon;
}

void Medusa::MoveTo(Vector moveToPosition)
{
	if (this->currentTween == nullptr) {
		this->isMoving = true;
		double distance = abs(moveToPosition.x - this->position.x);
		this->currentTween = this->cvGame->add->Tween(this->position.x, moveToPosition.x,(distance/this->moveSpeed)*DEFAULT_MS_PER_FRAME_FOR_ANIMATION)
			->SetOnFinish([this]() {
			this->currentTween = nullptr;
			this->isMoving = false;
		})->Start();
	}
}

void Medusa::Awake()
{
	this->SetVisible(true);
	this->body->SetEnable(true);
	this->PlayAnimation("move");
	this->moveTimer.reset();
	this->isAwake = true;
	MoveTo(this->simon->position);
}



void Medusa::OnSimonEnterRange(Simon * simon, bool isLeft)
{
	this->allowToDetectSimon = false;
	if (!this->isAwake) {
		this->cvGame->add->TimeOut(this->timeOutToAwake, [=]() {
			Awake();
		})->Start();

	}
}
