#include "Body.h"
#include "Sprite.h"
#include "Game.h"
namespace ggEngine {
	Body::Body(Game* game,Sprite * sprite)
	{
		this->sprite = sprite;
		this->width = sprite->GetWidth();
		this->height = sprite->GetHeight();
		this->orgWidth = sprite->GetImage()->GetWidth();
		this->orgHeight = sprite->GetImage()->GetHeight();
		this->enable = true;
		this->position = sprite->GetPosition();
		this->game = game;
		this->isAlive = true;
	}
	Body::~Body()
	{
	}
	void Body::StopMovement(bool stopVelocity)
	{
	}
	void Body::UpdateBounds()
	{
		if (CheckWorldBounds()) {
			if (blocked.down) {
				if (velocity.y > 0) {
					velocity.y *= -bounciness;
					position.y = WINDOW_HEIGHT - height;
				}
			}
		}
	}
	void Body::PreUpdate()
	{
		position = sprite->GetPosition();
		width = sprite->GetWidth();
		height = sprite->GetHeight();
	}
	void Body::UpdateMovement()
	{
		float timeStep = game->logicTimer.getDeltaTime();
		Vector lastAcceleration = acceleration;
		Vector force = (CalculateAirForce() + CalculateGravityForce());
		Vector temp = (velocity*timeStep + (0.5*lastAcceleration*timeStep*timeStep));
		position += temp * 100;
		Vector newAcceleration = force / mass;
		acceleration = (lastAcceleration + newAcceleration) / 2;
		velocity += acceleration*timeStep;
	}
	void Body::PostUpdate()
	{
		sprite->SetPosition(position);
	}
	bool Body::CheckWorldBounds()
	{
		blocked.Reset();
		if (position.x <= 0) {
			blocked.left = true;
			return true;
		}
		if (position.x + width >= WINDOW_WIDTH) {
			blocked.right = true;
			return true;
		}
		if (position.y + height >= WINDOW_HEIGHT) {
			blocked.down = true;
			return true;
		}
		if (position.y <= 0) {
			blocked.up = true;
			return true;
		}
		return false;
	}
	bool Body::MoveTo(int duration, int distance, int directionAngle)
	{
		return false;
	}
	void Body::SetSize(int width, int height, int offsetX, int offsetY)
	{
	}
	void Body::Reset(Vector newPosition)
	{
	}
	Body * Body::GetBounds(Body * obj)
	{
		return nullptr;
	}
	bool Body::HitTest(Vector position)
	{
		return false;
	}
	bool Body::OnFloor()
	{
		return false;
	}
	bool Body::OnCeiling()
	{
		return false;
	}
	bool Body::OnWall()
	{
		return false;
	}
	float Body::DeltaAbsX()
	{
		return 0.0f;
	}
	float Body::DeltaAbsY()
	{
		return 0.0f;
	}
	float Body::DeltaX()
	{
		return 0.0f;
	}
	float Body::DeltaY()
	{
		return 0.0f;
	}
	void Body::Destroy()
	{
		isAlive = false;
	}
	void Body::Render(D3DCOLOR color, bool filled)
	{
	}
	std::string Body::ToString()
	{
		return std::string();
	}
	void Body::Update()
	{
		PreUpdate();
		UpdateMovement();
		UpdateBounds();
		PostUpdate();
	}
	Vector Body::CalculateAirForce()
	{
		float a = -1 * 0.5*airDensity*objectCoeffecient*CalculateArea();
		Vector air(a*velocity.x*velocity.x, a*velocity.y*velocity.y);
		return air;
	}
	Vector Body::CalculateGravityForce()
	{
		return Vector(0,mass*gravity);
	}
	float Body::CalculateArea()
	{
		return 0.0f;
	}
}
