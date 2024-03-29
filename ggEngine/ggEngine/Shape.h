#pragma once
#include "GGObject.h"
#include "Matrix.h"
#include "ConstantEnum.h"
#include "Vector.h"
#include "Rect.h"
namespace ggEngine {
	class Shape: public GGObject {
	public:
		Shape() {
			this->anchor = Vector(0, 0);
		}
		virtual double GetArea() = 0;
		virtual void Transform(Vector position,double width, double height) = 0;
		virtual void Transform(Vector position) = 0;
		void SetAnchor(Vector anchor) {
			this->anchor = anchor;
		}
		void SetAnchor(double x, double y) {
			this->anchor.x = x;
			this->anchor.y = y;
		}
		virtual Rect GetRect();
		virtual double GetLeft() = 0;
		virtual double GetRight() = 0;
		virtual double GetUp() = 0;
		virtual double GetDown() = 0;
		virtual double GetWidth() = 0;
		virtual double GetHeight() = 0;
		virtual Vector GetPivotPoint() = 0;
		virtual void Translate(Vector translate) = 0;
		virtual void Translate(double x, double y) {
			Translate(new Vector(x, y));
		}
		Vector GetAnchor() { return this->anchor; }
	protected:

		Vector anchor;
	};
}