#pragma once
#include <d3d9.h>
#include "ISerializable.h"
namespace ggEngine {
	class Box : public ISerializable {
	public:
		Box(double x, double y, double w, double h, double vx, double vy);
		Box();
		double x, y;
		double w, h;
		double vx, vy;
		RECT GetRect() { return RECT{ (long)x,(long)y,(long)(x + w),(long)(y + h) }; }

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version);
	private:
	};
	template<class Archive>
	inline void Box::serialize(Archive & ar, const unsigned int version)
	{
		ar & x;
		ar & y;
		ar & w;
		ar & h;
		ar & vx;
		ar & vy;
	}
}