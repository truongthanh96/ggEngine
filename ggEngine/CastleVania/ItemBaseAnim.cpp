#include "ItemBaseAnim.h"
#include "CVGame.h"
#include "Simon.h"
#include "CVAdd.h"

ItemBaseAnim::ItemBaseAnim(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: CVSpriteAnimation(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->cvGame = cvGame;
	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(this->image->GetWidth(), this->image->GetHeight());
	this->body->allowGravity = true;
	this->events->onCollide = [this](GameObject *go, ColliderArg e) {
		Simon * simon = dynamic_cast<Simon*>(e.colliderObject);
		if (simon != nullptr) {
			OnSimonContact(simon, e);
		}
	};
	this->events->onCheckingCollide = [this](GameObject* go, ColliderArg e) {
		Tag tag = e.colliderObject->tag;
		switch (tag) {
		case ObjectType_LevelTwoBrick:
			return true;
		}
		return false;
	};
	this->tag = ObjectType_Item;
	this->visible = false;
	this->body->SetActive(false);
}

ItemBaseAnim::~ItemBaseAnim()
{
	if (cvGame->simon != nullptr) {
		cvGame->simon->body->RemoveCheckCollisionWith(this);
	}
	if (timeEvent != nullptr) timeEvent->Destroy();
}

void ItemBaseAnim::SetLiveTime(unsigned int liveTime)
{
	this->liveTime = liveTime;
}

void ItemBaseAnim::CheckCollisionToSimon(Simon * simon)
{
	simon->body->CheckCollisionTo(this);
}

void ItemBaseAnim::OnSimonContact(Simon * simon, ColliderArg e)
{

	Destroy();
}

void ItemBaseAnim::Destroy()
{
	
	GameObject::Destroy();
}

void ItemBaseAnim::Active()
{
	this->visible = true;
	this->body->SetActive(true);
	if (this->liveTime != -1) {
		this->timeEvent = this->cvGame->add->TimeOut(this->liveTime, [this]() {
			Destroy();
		});
	}
}

