#include "AnimationManager.h"
#include "TextureConstant.h"
#include "Simon.h"
#include "CVMap.h"

AnimationManager::AnimationManager(CVGame * cvGame) : ManagerBase(cvGame)
{

}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::PreloadAll()
{
	this->preload->Texture(TextureConstant::ANIMATION_BOSS_DEATH_TEXTURE, TextureConstant::ANIMATION_BOSS_DEATH_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ANIMATION_ENEMY_DEATH_TEXTURE, TextureConstant::ANIMATION_ENEMY_DEATH_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ANIMATION_HIT_TEXTURE, TextureConstant::ANIMATION_HIT_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ANIMATION_BREAKING_WALL_TEXTURE, TextureConstant::ANIMATION_BREAKING_WALL_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ANIMATION_TEXT_100_TEXTURE, TextureConstant::ANIMATION_TEXT_100_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ANIMATION_TEXT_400_TEXTURE, TextureConstant::ANIMATION_TEXT_400_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ANIMATION_TEXT_700_TEXTURE, TextureConstant::ANIMATION_TEXT_700_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ANIMATION_TEXT_1000_TEXTURE, TextureConstant::ANIMATION_TEXT_1000_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ANIMATION_TEXT_2000_TEXTURE, TextureConstant::ANIMATION_TEXT_2000_TEXTURE_PATH);

}

CVSpriteAnimation * AnimationManager::AddText100(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_TEXT_100_TEXTURE);
	CVSpriteAnimation *anim = new CVSpriteAnimation(this->cvGame, inf, 13, 9, 0, 1, 100);
	anim->CreateAnimation("text100", { 0, 0 , 0 , 0 , 0 }, false)->SetOnCompleted([anim](Animator*) {
		anim->Destroy();
	});
	anim->SetPosition(Vector(x, y));
	if (this->simonGroup != nullptr) {
		simonGroup->AddDrawObjectToList(anim);
	}
	anim->SetAnchor(-0.8, 0.5);
	anim->PlayAnimation("text100");
	return anim;
}

CVSpriteAnimation * AnimationManager::AddText400(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_TEXT_400_TEXTURE);
	CVSpriteAnimation *anim = new CVSpriteAnimation(this->cvGame, inf, 14, 9, 0, 1, 100);
	anim->CreateAnimation("text400", { 0, 0 , 0 , 0 , 0 }, false)->SetOnCompleted([anim](Animator*) {
		anim->Destroy();
	});
	anim->SetPosition(Vector(x, y));
	if (this->simonGroup != nullptr) {
		simonGroup->AddDrawObjectToList(anim);
	}
	anim->SetAnchor(-0.8, 0.5);
	anim->PlayAnimation("text400");
	return anim;
}

CVSpriteAnimation * AnimationManager::AddText700(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_TEXT_700_TEXTURE);
	CVSpriteAnimation *anim = new CVSpriteAnimation(this->cvGame, inf, 14, 8, 0, 1, 100);
	anim->CreateAnimation("text700", { 0, 0 , 0 , 0 , 0 }, false)->SetOnCompleted([anim](Animator*) {
		anim->Destroy();
	});
	anim->SetPosition(Vector(x, y));
	if (this->simonGroup != nullptr) {
		simonGroup->AddDrawObjectToList(anim);
	}
	anim->SetAnchor(-0.8, 0.5);
	anim->PlayAnimation("text700");
	return anim;
}

CVSpriteAnimation * AnimationManager::AddText1000(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_TEXT_1000_TEXTURE);
	CVSpriteAnimation *anim = new CVSpriteAnimation(this->cvGame, inf, 17, 9, 0, 1, 100);
	anim->CreateAnimation("text1000", { 0, 0 , 0 , 0 , 0 }, false)->SetOnCompleted([anim](Animator*) {
		anim->Destroy();
	});
	anim->SetPosition(Vector(x, y));
	if (this->simonGroup != nullptr) {
		simonGroup->AddDrawObjectToList(anim);
	}
	anim->SetAnchor(-0.8, 0.5);
	anim->PlayAnimation("text1000");
	anim->FlickeringChangeColorAnimationInfinity(500)->Start();
	return anim;
}

CVSpriteAnimation * AnimationManager::AddText2000(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_TEXT_2000_TEXTURE);
	CVSpriteAnimation *anim = new CVSpriteAnimation(this->cvGame, inf, 18, 9, 0, 1, 100);
	anim->CreateAnimation("text2000", { 0, 0 , 0 , 0 , 0 }, false)->SetOnCompleted([anim](Animator*) {
		anim->Destroy();
	});
	anim->SetPosition(Vector(x, y));
	if (this->simonGroup != nullptr) {
		simonGroup->AddDrawObjectToList(anim);
	}
	anim->SetAnchor(-0.8, 0.5);
	anim->PlayAnimation("text2000");
	anim->FlickeringChangeColorAnimationInfinity(500)->Start();
	return anim;
}

CVSpriteAnimation * AnimationManager::AddEnemyDeathAnimation(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_ENEMY_DEATH_TEXTURE);
	CVSpriteAnimation *anim = new CVSpriteAnimation(this->cvGame, inf, 8, 15, 0, 3, 100);
	anim->CreateAnimation("enemyDeath", 0, 2, false)->SetOnCompleted([anim](Animator*) {
		anim->Destroy();
	});
	anim->SetPosition(Vector(x, y));
	if (this->simonGroup != nullptr) {
		simonGroup->AddDrawObjectToList(anim);
	}
	anim->PlayAnimation("enemyDeath");
	return anim;
}

CVSpriteAnimation * AnimationManager::AddBossDeathAnimation(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_BOSS_DEATH_TEXTURE);
	CVSpriteAnimation *anim = new CVSpriteAnimation(this->cvGame, inf, 24, 31, 0, 3, 100);
	anim->CreateAnimation("bossDeath", {0, 1, 2, 0, 1, 2}, false)->SetOnCompleted([anim](Animator*) {
		anim->Destroy();
	});
	anim->SetPosition(Vector(x, y));
	if (simonGroup != nullptr) {
		simonGroup->AddDrawObjectToList(anim);
	}

	anim->PlayAnimation("bossDeath");
	return anim;
}

CVSpriteAnimation * AnimationManager::AddHitAnimation(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_HIT_TEXTURE);
	CVSpriteAnimation *anim = new CVSpriteAnimation(this->cvGame, inf, 8, 10, 0, 1, 100);
	anim->CreateAnimation("hit", 0, 0, false)->SetOnCompleted([anim](Animator*) {
		anim->Destroy();
	});
	anim->SetPosition(Vector(x, y));
	if (simonGroup != nullptr) {
		simonGroup->AddDrawObjectToList(anim);
	}
	anim->SetAnchor(0.8, 0.8);
	anim->PlayAnimation("hit");

	//this->cvGame->physics->EnablePhysics(anim);
	//anim->body->CreateRectangleRigidBody(anim->GetWidth(), anim->GetHeight());
	//anim->body->allowGravity = false;
	//anim->body->SetActive(false);

	return anim;
}

CVSprite ** AnimationManager::AddBreakingWallAnimation(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_BREAKING_WALL_TEXTURE);
	CVSprite**bricks = new CVSprite*[4];
	for (int i = 0; i < 4; i++) {
		bricks[i] = new CVSprite(this->cvGame, inf);
		CVSprite *br = bricks[i];

		this->cvGame->physics->EnablePhysics(br);
		br->body->CreateRectangleRigidBody(br->GetWidth(), br->GetHeight());
		br->body->SetEnable(true);
		br->body->allowGravity = true;
		br->body->rigidBody->SetAnchor(0, 0);
		br->body->SetActive(true);
		this->cvGame->eventManager->EnableCameraEvent(br);

		br->events->onOutOfCamera = [br](GameObject *go, EventArg e){
			br->Destroy();
		};

		if (simonGroup != nullptr) {
			simonGroup->AddDrawObjectToList(br);
		}
		br->SetAlive(true);
		br->SetPosition(Vector(x, y),true);
	}
	bricks[0]->body->AddForce(1.5, Vector(1, -2));
	bricks[1]->body->AddForce(2.0, Vector(-1, -1.5));
	bricks[2]->body->AddForce(1.3, Vector(1, -0.5));
	bricks[3]->body->AddForce(1.7, Vector(-1, -0.5));
	return bricks;
}
