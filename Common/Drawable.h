#pragma once
#include <vector>
#include "geometry.h"


class Drawable {
public:
	virtual std::vector<int> face(int index) = 0;
	virtual int nfaces() = 0;
	virtual Vec3f vert(int index) = 0;
	virtual int nverts() = 0;
	virtual ~Drawable() {}
	virtual Vec2f uv(int index) = 0;
};