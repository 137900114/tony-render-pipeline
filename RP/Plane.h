#pragma once
#include "config.h"

class Plane : public Drawable {
public:
	Plane(Vec3f v0,Vec3f v1,Vec3f v2){
		withNormal = true;
		_normal = cross(v0 - v1, v0 - v2).normalize();
		v[0] = v0, v[1] = v1, v[2] = v2;
		v[3] = v0 + v2 - v1;
	}
	int nfaces() override { return 2; }
	std::vector<int> face(int nface) override{
		if (nface == 0) {
			std::vector<int> result = {0,1,2};
			return result;
		}
		std::vector<int> result = {0,2,3};
		return result;
	}
	int nverts() override { return 4; }
	Vec3f vert(int nvert) override { return v[nvert]; }
	Vec2f uv(int nvert) override { return Vec2f(0, 0); }
	Vec3f normal(int nvert) override { return _normal; }
private:
	Vec3f v[4],_normal;
};