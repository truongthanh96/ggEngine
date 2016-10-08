#include "SpriteAnimation.h"
#include "Animator.h"
#include "Texture.h"
#include "Debug.h"
namespace ggEngine {
	SpriteAnimation::SpriteAnimation(DrawManager *drawManager, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame) :Sprite(drawManager)
	{
		this->spriteAnimationType = SA_RectangleSheet;
		this->currentFrame = defaultFrame;
		this->isRunningAnimation = false;
		SetImage(image, frameWidth, frameHeight, numberOfFrame);
	}
	SpriteAnimation::~SpriteAnimation()
	{
		for (std::map<std::string, Animator*>::iterator it = this->animatorMap.begin(); it != this->animatorMap.end(); ++it) {
			delete (it->second);
		};
		animatorMap.clear();
		if(currentAnimation!=NULL) delete currentAnimation;
	}
	void SpriteAnimation::Draw(Matrix translatedWorldMatrix)
	{
		Transform(translatedWorldMatrix,spriteHandle);
		RECT srcRect;
		if (!visible) return;
		if (this->isRunningAnimation && this->currentAnimation->isFinished) this->isRunningAnimation = false;
		if (this->isRunningAnimation) {
			srcRect = this->currentAnimation->GetNextRect();
			this->currentFrame = this->currentAnimation->currentFrame;
		}
		else {
			int currentFrameRow = ((this->currentFrame) / this->framePerRow);
			int currentFrameColumn = (this->currentFrame - ((currentFrameRow)*this->framePerRow));
			int top = this->frameHeight*currentFrameRow;
			int left = this->frameWidth*currentFrameColumn;
			int right = left + this->frameWidth;
			int bottom = top + this->frameHeight;
			srcRect = { left,top,right,bottom };
		}
		if (spriteHandle->Begin(D3DXSPRITE_ALPHABLEND) == D3D_OK)
		{
			spriteHandle->Draw(this->GetImage()->GetTexture()->GetDxTexture(), &srcRect, NULL, NULL, D3DXCOLOR(255, 255, 255, opacity));
			spriteHandle->End();
		}
	}
	void SpriteAnimation::Destroy()
	{
		GameObject::Destroy();
	}
	void SpriteAnimation::CreateAnimation(std::string animationName, int startFrame, int endFrame, bool isLoop)
	{
		if (endFrame > this->numberOfFrame) {
			Debug::Warning("End frame is bigger than number of frame.");
			endFrame = this->numberOfFrame;
		}
		if (startFrame < 0) {
			Debug::Warning("Start frame must not be negative.");
			startFrame = 0;
		}
		animatorMap[animationName] = new Animator(startFrame, endFrame, this, isLoop);
	}
	void SpriteAnimation::PlayAnimation(std::string animationName)
	{
		std::map<std::string, Animator*>::iterator it = this->animatorMap.find(animationName);
		if (it != this->animatorMap.end())
		{
			this->currentAnimation = (it->second);
			this->isRunningAnimation = true;
		}
		else {
			Debug::Warning("No animation found  with key " + animationName);
		}
	}
	void SpriteAnimation::SetImage(SpriteInfo * image, int frameWidth, int frameHeight, int numberOfFrame)
	{
		this->image = image;
		this->height = this->frameHeight = frameHeight;
		this->width = this->frameWidth = frameWidth;
		this->framePerRow = this->image->GetWidth() / frameWidth;
		this->framePerColumn = this->image->GetHeight() / frameHeight;
		int num = this->framePerRow*this->framePerColumn;
		if (num > numberOfFrame && numberOfFrame != 0) {
			this->numberOfFrame = numberOfFrame;
		}
		else {
			this->numberOfFrame = num;
		}
	}
	void SpriteAnimation::SetWidth(float width)
	{
		this->scale.x = ((float)width / this->frameWidth);
		this->width = width;
	}
	void SpriteAnimation::SetHeight(float height)
	{
		this->scale.y = (float)height / this->frameHeight;
		this->height = height;
	}
	void SpriteAnimation::SetScale(float x, float y)
	{
		GameObject::SetScale(x, y);
		this->width = this->frameWidth*x;
		this->height = this->frameHeight*y;
	}
	float SpriteAnimation::GetWidth()
	{
		//return this->frameWidth*this->scale.x;
		return this->width;
	}
	float SpriteAnimation::GetHeight()
	{
		//return this->frameHeight*this->scale.y;
		return this->height;
	}
}