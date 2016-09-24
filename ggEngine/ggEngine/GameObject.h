#pragma once
#include "Vector.h"
#include "ConstantEnum.h"
#include "GGObject.h"
namespace ggEngine {
	class GameObject :public GGObject {
	public:
		GameObject();
		~GameObject();
		Vector GetPosition();
		void SetPosition(Vector vector);
		void SetPosition(float x, float y);
		void SetX(float x) { this->position.x = x; }
		void SetY(float y) { this->position.y = y; }
		float GetX() { return this->position.x; }
		float GetY() { return this->position.y; }
		void SetVisible(bool visible) { this->visible = visible; }
		bool IsVisible() { return this->visible; }
		void Destroy();
		Vector GetScale() { return this->scale; }
		void SetScale(Vector vector) { this->scale = vector; }
		void SetScale(float x, float y){ this->scale.x = x; this->scale.y = y; }
		void SetRotate(float angle){ this->rotate = angle; }
		float GetRotate(){ return this->rotate; }
		bool GetAlive() { return this->alive; }
	protected:
		Vector position;
		Vector scale;
		bool alive;
		bool visible;
		float rotate;
	};
}