#pragma once
#include "GGObject.h"
#include <d3d9.h>
#include "Vector.h"
#include <cmath>
#include "ConstantEnum.h"
#include <string>
#include "RectangleShape.h"
#include <functional>
namespace ggEngine {
	struct Direction {
		bool none = false;
		bool any = false;
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		void Reset() {
			none = false;
			any = false;
			up = false;
			down = false;
			left = false;
			right = false;
		}
	};
	class Sprite;
	class Game;
	class Body :GGObject {
	public:
		Body(Game *game,Sprite *sprite);
		~Body();
		int width;
		int height;
		int orgWidth;
		int orgHeight;
		float rotation = 0;
		float preRotation;
		Shape* bodyShape;
		//Force modifier
		/*Air*/
		float airDensity = 0.1;
		float objectCoeffecient = 0.47;
		bool allowAirResistance;
		/*Gravity*/
		float mass = 0.4;
		float gravity = 9.81;
		bool allowGravity = true;
		/*Vicious damping*/
		float dampingCoeffecient = 0.4;
		float alphaAngle = 0;
		bool allowDamping = true;
		/*Rotation*/

		float bounciness = 0.4;
		Vector velocity;
		Vector newVelocity;
		Vector deltaMax;
		Vector acceleration;
		Vector drag;
		Vector bound;
		Vector worldBounce;
		std::function<void()> *onWorldBounds;
		std::function<void(Body*)> *onCollide;
		std::function<void(Body*)> *onOverlap;
		Vector maxVelocity;
		Vector friction;
		float offsetX = 0;
		float offsetY = 0;
		float angularVelocity = 0;
		float angularAcceleration = 0;
		float angularDrag = 0;
		float maxAngular = 0;
		float angle = 0;
		float speed = 0;
		bool immovable = false;
		bool moves = true;
		bool customSeperateX = false;
		bool customeSeperateY = false;
		float overlapX = 0;
		float overlapY = 0;
		float overlapR = 0;
		bool embedded = false;
		bool collideWorldBounds = false;
		Game* game;
		Sprite* sprite;
		Vector position;
		Direction checkCollision;
		Direction touching ;
		Direction wasTouching;
		Direction blocked;
		bool enable = true;
		bool dirty = false;
		bool syncBounds = false;
		bool isMoving = false;
		bool stopVelocityOnCollide = true;
		int moveTimer = 0;
		int moveDistance = 0;
		int moveDuration = 0;
		//TO DO: put a moveTarger here
		Vector moveEnd;
		std::function<void()> *onMoveComplete;
		std::function<void()> *movementCallback;
		GGObject *movementCallbackContext;
		//Public method 
		void StopMovement(bool stopVelocity);
		bool CheckWorldBounds();
		bool MoveTo(int duration, int distance, int directionAngle);
		void SetSize(int width, int height, int offsetX, int offsetY);
		void Reset(Vector newPosition);
		Body* GetBounds(Body *obj);
		bool HitTest(Vector position);
		bool OnFloor();
		bool OnCeiling();
		bool OnWall();
		float DeltaAbsX();
		float DeltaAbsY();
		float DeltaX();
		float DeltaY();
		void Destroy();
		void Render(D3DCOLOR color, bool filled);
		std::string ToString();
		void Update();
		bool IsAlive() { return this->isAlive; }
		void AddForce(float force, float angleInRadian);
		void AddForce(float force, Vector angleInVector);
	private:
		Vector CalculateAirForce();
		Vector CalculateGravityForce();
		Vector CalculateDampingForce();
		float CalculateArea();
		void UpdateBounds();
		void PreUpdate();
		void UpdateMovement();
		void PostUpdate();
		bool isAlive;
	};
}