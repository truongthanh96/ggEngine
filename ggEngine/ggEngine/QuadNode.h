#pragma once
#include <vector>
#include <d3d9.h>
#include "Vector.h"
#include "GameObject.h"
namespace ggEngine {
	class QuadTree;
	class QuadNode: public GameObject {
	public:
		QuadNode(QuadTree *quadTree,double width, double height,int id, int leftTop, int rightTop, int leftBottom, int rightBottom);
		QuadNode(QuadTree *quadTree, double width, double height,int id, bool isCollidedObject);
		~QuadNode();
		RECT GetRect();
		void SetObject(std::vector<GameObject*> objectList);
		std::vector<GameObject*> GetObjectFromNode();
		QuadNode* GetLeftTop();
		QuadNode* GetRightTop();
		QuadNode* GetLeftBottom();
		QuadNode* GetRightBottom();
		void UpdateWorldPosition() override;
		void UpdateWorldPositionFromTileMap();
		bool IsLeafNode() { return this->isLeafNode; }
		// Inherited via DrawObject
		void Draw() override;
	private:
		bool isCollidedObject;
		bool isLeafNode;
		int leftTop, rightTop, leftBottom, rightBottom;
		std::vector<GameObject*> objectList;
		double width, height;
		int id;
		QuadTree *quadTreeParent;

	};
	
}