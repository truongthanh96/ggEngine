#include "Cross.h"
#include "Simon.h"

Cross::Cross(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

Cross::~Cross()
{
}

void Cross::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->infoPanel->item->SetImage(this->image);
	Destroy();
}