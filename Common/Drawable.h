#pragma once
#include <vector>
#include "geometry.h"


class Drawable {
public:
	virtual std::vector<int> face(int nface) = 0;
	virtual int nfaces() = 0;
	virtual Vec3f vert(int nvert) = 0;
	virtual int nverts() = 0;
	virtual ~Drawable() {}
	virtual Vec2f uv(int nvert) = 0;

	virtual Vec3f normal(int nvert) { return Vec3f(0, 0, 0); }

	bool isWithNormal() { return withNormal; }
protected:
	bool withNormal;
};