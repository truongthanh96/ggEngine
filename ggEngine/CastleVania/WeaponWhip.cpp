#include "WeaponWhip.h"
#include "CVGame.h"
#include "Simon.h"


WeaponWhip::WeaponWhip(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: CVSpriteAnimation(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->SetAnchor(0.65, 0.5);
	this->SetScale(1, 1);
	this->SetVisible(false);

	//standardWhip
	this->CreateAnimation("1", 0, 2, false)->SetOnCompleted([this](Animator*) {
		this->PlayAnimation("after1");
	});
	this->CreateAnimation("after1", 2, 2, false)->SetOnCompleted([this](Animator*) {
		this->SetVisible(false);
	});

	//shortWhip
	this->CreateAnimation("2", 3, 5, false)->SetOnCompleted([this](Animator*) {
		this->PlayAnimation("after2");
	});
	this->CreateAnimation("after2", 5, 5, false)->SetOnCompleted([this](Animator*) {
		this->SetVisible(false);
	});

	//longWhip
	this->CreateAnimation("3", 6, 8, false)->SetOnCompleted([this](Animator*) {
		this->PlayAnimation("after3");
	});
	this->CreateAnimation("after3", 8, 8, false)->SetOnCompleted([this](Animator*) {
		this->SetVisible(false);
	});

	//this->cvGame->physics->EnablePhysics(this);
	//this->body->CreateRectangleRigidBody(50, 50);//
	//this->body->allowGravity = false;
	//this->body->allowWorldBound = false;
	//this->body->rigidBody->SetAnchor(0.5, 0.5);
	//this->body->SetActive(false);

	//this->cvGame->eventManager->EnableSpriteAnimationEvent(this);
	//this->events->onAnimationCompleted = [this](GameObject *go, AnimationArg e) {
	//	//this->Destroy();
	//	this->SetVisible(false);
	//	//this->body->SetEnable(false);
	//	//this->ResetAnimation(e.animationName);
	//};
	this->whipVersion = 1;
}


WeaponWhip::~WeaponWhip()
{
}

void WeaponWhip::SetWhipVersion(int version)
{
	this->whipVersion = version;
	if (this->whipVersion < 1)
		this->whipVersion = 1;
	if (this->whipVersion > 3)
		this->whipVersion = 3;
}

void WeaponWhip::UpgradeWhip()
{
	this->whipVersion++;
	if (this->whipVersion > 3)
		this->whipVersion = 1;
}

void WeaponWhip::Attack(bool isLeft)
{
	if (!isLeft)
		this->SetScale(-1, 1);
	else this->SetScale(1, 1);
	
	//this->body->SetEnable(true);

	auto anim = this->PlayAnimation(std::to_string(this->whipVersion));
	//this->SetFrame(anim->startFrame);
	this->SetVisible(true);
}

void WeaponWhip::StandAttack(bool isLeft)
{
	this->SetAnchor(0.64, 0.5);
	this->Attack(isLeft);
}

void WeaponWhip::ClimbUpAttack(bool isLeft)
{
	this->SetAnchor(0.62, 0.5);
	this->Attack(isLeft);
}

void WeaponWhip::ClimbDownAttack(bool isLeft)
{
	this->SetAnchor(0.64, 0.55);
	this->Attack(isLeft);
}

void WeaponWhip::KneelAttack(bool isLeft)
{
	this->SetAnchor(0.64, 0.25);
	this->Attack(isLeft);
}

void WeaponWhip::Draw()
{
	CVSpriteAnimation::Draw();
}

void WeaponWhip::UpdateWorldPosition()
{
	CVSpriteAnimation::UpdateWorldPosition();
}

