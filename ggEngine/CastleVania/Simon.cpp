#include "Simon.h"
#include "CVGame.h"
#include "CVAdd.h"
#include "ItemManager.h"
#include "WeaponManager.h"
#include "TileLadder.h"
Simon::Simon(CVGame *cvGame, SpriteInfo * image,InfoPanel *infoPanel, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: CharacterBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->weaponManager = cvGame->weaponManager;

	this->tag = ObjectType_Simon;
	this->health = 16;
	this->maxHealth = 16;
	this->infoPanel = infoPanel;
	this->SetPosition(0, 0);
	this->SetAnchor(0.5, 0.5);
	this->SetScale(1, 1);
	this->SetHealth(health);
	this->CreateAnimation("idle", 0, 0, true);
	this->CreateAnimation("move", 1, 2, true);
	this->CreateAnimation("kneel", 4, 4, true);
	this->CreateAnimation("climbDown", 5, 6, true);
	this->CreateAnimation("climbDownIdle", 5, 5, true);
	this->CreateAnimation("climbUp", 7, 8, true);
	this->CreateAnimation("climbUpIdle", 7, 7, true);
	this->CreateAnimation("behind", 9, 9, true);
	this->CreateAnimation("hurt", 10, 10, true);
	this->CreateAnimation("death", 11, 11, true);

	//Create "after ... attack" to double the frame which whip is shown longest
	//Stand Attack
	this->CreateAnimation("standAttack", { 12,13,14,14 }, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});

	// Kneel Attack
	this->CreateAnimation("kneelAttack", { 15,16,17,17 }, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});

	//Climb Down Attack
	this->CreateAnimation("climbDownAttack", { 18,19,20,20 }, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});

	//Climb Up Attack
	this->CreateAnimation("climbUpAttack", { 21,22,23,23 }, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});




	this->cvGame->physics->EnablePhysics(this);
	//this->body->SetPhysicsMode(PhysicsMode_AABBSweptMix);
	this->body->CreateRectangleRigidBody(14, 26);
	this->body->syncBounds = false;
	this->body->rigidBody->SetAnchor(0.5, 0.32);
	this->body->allowGravity = true;
	this->body->allowWorldBounciness = false;
	this->body->allowWorldBlock = true;
	this->events->onCheckingCollide = [this](GameObject *object, ColliderArg e) {
		GameObject *otherObject = e.colliderObject;
		Tag type = otherObject->tag;
		switch (type) {
		case ObjectType_LadderDownLeft:
			//this->ladderState = LadderDownLeft;
			return false;
		case ObjectType_LadderDownRight:
			//this->ladderState = LadderDownRight;
			return false;
		case ObjectType_LadderUpLeft:
			/*if (e.blockDirection.down) {
				this->ladderState = LadderUpLeft;
				this->grounding = GroundingBrick;
				return true;
			}*/
			return false;
		case ObjectType_LadderUpRight:
			//if (e.blockDirection.down && this->isClimbingUp) {
			/*if (this->isClimbingUp){
				this->ladderState = LadderUpRight;
				this->grounding = GroundingBrick;
				return true;
			}*/
			return false;
		case ObjectType_Static:
			return true;
		case ObjectType_LevelTwoBrick:
			return true;
		default:
			return false;
		}
		return false;

	};
	this->events->onCollide = [this](GameObject *object, ColliderArg e) {
		GameObject *otherObject = e.colliderObject;
		Tag type = otherObject->tag;
		switch (type) {
		case ObjectType_LevelTwoBrick:
			break;
		case ObjectType_Candle:
			//g_debug.Log("Collided with candle");
			break;
		case ObjectType_LadderDownLeft:
			tileLadder = dynamic_cast<TileLadder*>(otherObject);
			g_debug.Log("Overlap with ladder!");
			break;
		case ObjectType_LadderDownRight:
			tileLadder = dynamic_cast<TileLadder*>(otherObject);
			g_debug.Log("Overlap with ladder!");
			break;
		case ObjectType_LadderUpLeft:
			tileLadder = dynamic_cast<TileLadder*>(otherObject);
			g_debug.Log("Overlap with ladder!");
			break;
		case ObjectType_LadderUpRight:
			tileLadder = dynamic_cast<TileLadder*>(otherObject);
			g_debug.Log("Overlap with ladder!");
			break;
		case ObjectType_Static:
		case ObjectType_Item:
			if (otherObject->events->onCollide != nullptr) {
				ColliderArg	o = Physics::CreateOppositeColliderArg(e, object);
				otherObject->events->onCollide(otherObject, o);
			}
			break;
		default:
			break;
		}

	};
	//this->events->onOverlap = [this](GameObject *go, ColliderArg e) {
	//	GameObject *otherObject = e.colliderObject;
	//	Tag type = otherObject->tag;
	//	this->tileLadder = nullptr;
	//	switch (type) {
	//	case ObjectType_LadderDownLeft:
	//	case ObjectType_LadderDownRight:
	//	case ObjectType_LadderUpLeft:
	//	case ObjectType_LadderUpRight:
	//		tileLadder = dynamic_cast<TileLadder*>(otherObject);
	//		g_debug.Log("Overlap with ladder!");
	//		break;
	//	}
	//};
	this->events->onWorldBounds = [this](GameObject *go, ColliderArg e) {
		if (e.blockDirection.down) {
			this->grounding = SimonGrounding_Brick;
		}
	};

	this->cvGame->eventManager->EnableKeyBoardInput(this);
	this->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		/*if (this->GetHealth() <= 0) {
			this->Death();
			return;`
		}*/

		if (this->incompleteAnim != "") {
			this->PlayAnimation(incompleteAnim);
			return;
		}

		switch (this->grounding) {
			case SimonGrounding_Brick:
				if (CheckKeyValid(e) == false)
					this->Idle();
				else {
					CheckKeyPressNormal(e);
#ifdef _DEBUG
					CheckKeyWhenDebug(e);
#endif // DEBUG
				}
				break;

			case SimonGrounding_None:
				CheckKeyPressJumping(e);
				break;
			}
	};
	
	this->SetUpKeyControl();
	this->SetUpTestKeyControl();
	this->shot = 1;
	this->score = 0;
	this->stagePoint = 1;
	this->heartPoint = 99;
	this->pPoint = 3;
	this->grounding = SimonGroundingType::SimonGrounding_Brick;
	this->subWeapon = SimonSubWeaponType::SubWeapon_None;
}

Simon::~Simon()
{
	if (this->weaponWhip != nullptr) {
		delete this->weaponWhip;
	}
}

void Simon::SetHealth(int heath)
{
	this->health = heath;
	if (this->health < 0) this->health = 0;
	if (this->health > this->maxHealth) this->health = this->maxHealth;
	if (infoPanel != nullptr) {
		infoPanel->SetPlayerHealth(this->health);
	}
	if (this->health == 0) Death();
}

void Simon::Attack()
{
	this->weaponManager->AddWeapon(this, position.x, position.y, this->isLeft, this->parentGroup);
}

void Simon::WhipAttack()
{
}

void Simon::AddWhip()
{
	this->weaponWhip = this->weaponManager->AddWeaponWhip(0, 8, isLeft, this->parentGroup);
	this->weaponWhip->SetAnchor(0.64, 0.5);
	this->weaponWhip->SetTransformBasedOn(this);
}

void Simon::Idle()
{
	this->PlayAnimation("idle");
	this->body->velocity.x = 0;
}

void Simon::MoveLeft()
{
	this->PlayAnimation("move");
	ChangeFacingDirection(true);
	this->body->velocity.x = -CharacterConstant::SIMON_MOVE_FORCE;
}

void Simon::MoveRight()
{
	this->PlayAnimation("move");
	ChangeFacingDirection(false);
	this->body->velocity.x = CharacterConstant::SIMON_MOVE_FORCE;
}

void Simon::Jump()
{
	if (grounding == SimonGrounding_Brick)
	{
		this->PlayAnimation("kneel");
		this->body->velocity.y = -CharacterConstant::SIMON_JUMP_FORCE;
		//this->weaponWhip->body->velocity.y = -CharacterConstant::SIMON_JUMP_FORCE;
		grounding = SimonGrounding_None;
	}
}

void Simon::Kneel()
{
	this->PlayAnimation("kneel");
	this->body->velocity.x = 0;
}

void Simon::ClimbUpLeft()
{
	this->PlayAnimation("climbUp");
	//this->isClimbingUp = true;
	ChangeFacingDirection(true);
	this->body->velocity.x = -CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = -CharacterConstant::SIMON_CLIMB_FORCE;
}

void Simon::ClimbUpRight()
{
	this->PlayAnimation("climbUp");
	//this->isClimbingUp = true;
	ChangeFacingDirection(false);
	this->body->velocity.x = CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = -CharacterConstant::SIMON_CLIMB_FORCE;
}

void Simon::ClimbDownLeft()
{
	this->PlayAnimation("climbDown");
	//this->isClimbingUp = false;
	ChangeFacingDirection(true);
	this->body->velocity.x = -CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = CharacterConstant::SIMON_CLIMB_FORCE;
}

void Simon::ClimbDownRight()
{
	this->PlayAnimation("climbDown");
	//this->isClimbingUp = false;
	ChangeFacingDirection(false);
	this->body->velocity.x = CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = CharacterConstant::SIMON_CLIMB_FORCE;
}

void Simon::ClimbIdle()
{
	this->body->velocity.x = 0;
	this->body->velocity.y = 0;

	/*if (this->isClimbingUp)
		PlayAnimation("climbUpIdle");
	else
		PlayAnimation("climbDownIdle");*/
}

void Simon::ClimbUpFinish()
{
	this->PlayAnimation("Idle");
	this->body->velocity.x = 0;
	this->body->velocity.y = 0;
	this->grounding = SimonGrounding_Brick;
}

void Simon::Hurt()
{
	this->PlayAnimation("hurt");
	this->Blind();
	//this->body->SetEnable(false);

	Vector direction(1, -3);
	if (isLeft)
		direction.x = -1;
	this->body->AddForce(hurtForce, direction);

	this->cvGame->add->TimeOut(2000, [this] {
		//this->body->SetEnable(true);
	})->Start();

}

void Simon::Death()
{
	this->PlayAnimation("death");
	this->body->velocity.x = 0;
}

void Simon::StandAttack()
{
	this->body->velocity.x = 0;
	this->PlayAnimation("standAttack");
	this->incompleteAnim = "standAttack";
	//this->WhipAttack();
	this->weaponWhip->StandAttack(isLeft);
}

void Simon::KneelAttack()
{
	this->body->velocity.x = 0;
	this->PlayAnimation("kneelAttack");
	this->incompleteAnim = "kneelAttack";
	this->weaponWhip->KneelAttack(isLeft);
}

void Simon::ClimbDownAttack()
{
	this->body->velocity.x = 0;
	this->body->velocity.y = 0;
	this->PlayAnimation("climbDownAttack");
	this->incompleteAnim = "climbDownAttack";
	this->weaponWhip->ClimbDownAttack(isLeft);
}

void Simon::ClimbUpAttack()
{
	this->body->velocity.x = 0;
	this->body->velocity.y = 0;
	this->PlayAnimation("climbUpAttack");
	this->incompleteAnim = "climbUpAttack";
	this->weaponWhip->ClimbUpAttack(isLeft);
}

void Simon::ClimbAttack()
{
	//if (this->isClimbingUp)
	//	this->ClimbUpAttack();
	//else
	//	this->ClimbDownAttack();
}

void Simon::LoseHealth(int health)
{
	this->health -= health;
	if (this->health < 0) this->health = 0;
	if (infoPanel != nullptr) {
		infoPanel->SetPlayerHealth(this->health);
	}
	if (this->health == 0) Death();
}

void Simon::GainHealth(int health)
{
	this->health += health;
	if (this->health > this->maxHealth) this->health = this->maxHealth;
	if (infoPanel != nullptr) {
		infoPanel->SetPlayerHealth(this->health);
	}
}

void Simon::IncreaseScore(int score)
{
	this->score += score;
	this->infoPanel->SetScore(this->score);
}

void Simon::IncreaseState()
{
	if(infoPanel!=nullptr) this->infoPanel->SetState(++this->stagePoint);
}

void Simon::IncreaseHeartPoint(int point)
{
	this->heartPoint += point;
	if (infoPanel != nullptr) this->infoPanel->SetLife(heartPoint);
}

void Simon::DecreaseHeartPoint(int point)
{
	this->heartPoint = (heartPoint - point <= 0) ? 0 : heartPoint - point;
	if (infoPanel != nullptr) this->infoPanel->SetLife(this->heartPoint);
}

void Simon::DescreasePPoint(int point)
{
	this->pPoint = (pPoint - point <= 0) ? 0 : pPoint - point;
	if (infoPanel != nullptr) this->infoPanel->SetLife(this->pPoint);
}

void Simon::SetSubWeapon(SimonSubWeaponType weaponType, SpriteInfo * image)
{
	this->subWeapon = weaponType;
	this->infoPanel->SetItemImage(image);
}



void Simon::SetShot(int shot, SpriteInfo * image)
{
	this->shot = shot;
	this->infoPanel->itemShot->SetImage(image);
}

void Simon::UpgradeWhip()
{
	this->weaponWhip->UpgradeWhip();

	this->Blind();
	// Will be changed to stopTime
	this->cvGame->eventManager->DisableKeyBoardInput(this);
	this->body->velocity.x = 0;
	this->Idle();
	this->cvGame->add->TimeOut(2000, [this] {
		this->cvGame->eventManager->EnableKeyBoardInput(this);
	})->Start();
}

void Simon::Blind()
{
	this->cvGame->add->Loop(100, 20, [this] {
		this->SetVisible(!this->IsVisible());
	})->Start();
}





void Simon::SetUpKeyControl()
{
	controlKey[SimonControl_Left] = DIK_LEFT;
	controlKey[SimonControl_Right] = DIK_RIGHT;
	controlKey[SimonControl_Up] = DIK_UP;
	controlKey[SimonControl_Down] = DIK_DOWN;
	controlKey[SimonControl_TurboA] = DIK_C;
	controlKey[SimonControl_TurboB] = DIK_V;
	controlKey[SimonControl_A] = DIK_Z;
	controlKey[SimonControl_B] = DIK_X;
}

void Simon::SetUpTestKeyControl()
{
	controlKey[SimonControl_Num1] = DIK_1;
	controlKey[SimonControl_Num2] = DIK_2;
	controlKey[SimonControl_Num3] = DIK_3;
	controlKey[SimonControl_Num4] = DIK_4;
	controlKey[SimonControl_Num5] = DIK_5;
	controlKey[SimonControl_Num6] = DIK_6;
	controlKey[SimonControl_Num7] = DIK_7;
	controlKey[SimonControl_Num8] = DIK_8;
	controlKey[SimonControl_Num9] = DIK_9;
	controlKey[SimonControl_Num0] = DIK_0;
}

void Simon::CheckKeyWhenDebug(KeyBoardEventArg e)
{
	this->subWeapon = SimonSubWeaponType::SubWeapon_None;
	if (e.isPress(controlKey[SimonControl_Num1])) {
		this->subWeapon = SimonSubWeaponType::SubWeapon_Axe;
	}
	if (e.isPress(controlKey[SimonControl_Num2])) {
		this->subWeapon = SimonSubWeaponType::SubWeapon_Boomerang;
	}
	if (e.isPress(controlKey[SimonControl_Num3])) {
		this->subWeapon = SimonSubWeaponType::SubWeapon_Dagger;
	}
	if (e.isPress(controlKey[SimonControl_Num4])) {
		this->subWeapon = SimonSubWeaponType::SubWeapon_HolyWater;
	}
	if (e.isPress(controlKey[SimonControl_Num5])) {
		this->subWeapon = SimonSubWeaponType::SubWeapon_StopWatch;
	}
	if (e.isPress(controlKey[SimonControl_Num6])) {
	}
	if (e.isPress(controlKey[SimonControl_Num7])) {
		return;
	}
	if (e.isPress(controlKey[SimonControl_Num8])) {
		return;
	}
	if (e.isPress(controlKey[SimonControl_Num9])) {
		return;
	}
	if (e.isPress(controlKey[SimonControl_Num0])) {
		return;
	}
	this->Attack();
}

bool Simon::CheckKeyValid(KeyBoardEventArg e)
{
	int n = sizeof(controlKey) / sizeof(*controlKey);
	for (int i = 0; i < n; i++) {
		if (e.isPress(controlKey[i]))
			return true;
	}
	return false;
}

void Simon::CheckKeyPressNormal(KeyBoardEventArg e)
{
	if (e.isPress(controlKey[SimonControl_Left])) {
		this->MoveLeft();
	}

	if (e.isPress(controlKey[SimonControl_Right])) {
		this->MoveRight();
	}

	else {
		if (e.isPress(controlKey[SimonControl_Down]))
			this->Kneel();
		if (e.isPress(controlKey[SimonControl_B]))
			this->StandAttack();
	}
	if (e.isPress(controlKey[SimonControl_TurboB])) {
		this->Attack();
	}

	if (e.isPress(controlKey[SimonControl_A])) {
		this->Jump();
		this->grounding = SimonGrounding_None;
	}

	if (e.isPress(controlKey[SimonControl_B])
		&& e.isPress(controlKey[SimonControl_Down])) {
		this->KneelAttack();
	}
}

void Simon::CheckKeyPressJumping(KeyBoardEventArg e)
{
	if (e.isPress(controlKey[SimonControl_B]))
		this->StandAttack();
}
