#include "TestState.h"
#include "Add.h"
#include "Preload.h"
#include "Game.h"
#include "Physics.h"
#include "Body.h"
TestState::TestState(Game *game):State(game)
{
}
TestState::~TestState()
{
}
void TestState::Init(){

}
void TestState::Preload(){
	this->preload->Texture("kitty", "Resource/kitty.bmp");
	this->preload->Texture("girl", "Resource/girl.jpg");
}
void TestState::Create()
{
	this->test = 0;
	Group* group = this->add->Group();
	//sprite1 = this->add->SpriteAnimation(50,50,"kitty", 92, 60, group, 0);
	sprite2 = this->add->Sprite(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT/2.0, "default", 0, group);
	sprite2->SetAnchor(0, 0);
	sprite3 = this->add->Sprite(1, 0, "default", 0, group);
	//sprite1->CreateAnimation("MoveLeft", 0, 5, true);
	//sprite1->CreateAnimation("MoveRight", 6, 11, true);
	//sprite1->SetScale(1.3, 1.4);
	//game->physics->EnablePhysics(sprite1);
	//sprite1->body->AddForce(1, Vector(1, 0));
	//sprite1->PlayAnimation("MoveRight");
	
}
void TestState::Update()
{
	sprite3->SetX(sprite3->GetX() + 1);
	sprite3->SetY(sprite3->GetY() + 1);
}
void TestState::PreRender()
{
}
void TestState::Render()
{
}
void TestState::Pause()
{
}
void TestState::Resume()
{
}
void TestState::ShutDown()
{
}