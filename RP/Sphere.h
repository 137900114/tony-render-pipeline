#pragma once
#include "config.h"


class Sphere : public Drawable {
public:
	Sphere(Vec3f o, float radius = 1, int samples = 36) :
		o(o), radius(radius), samples(samples) {
		withNormal = true;
	}

	Vec3f vert(int nvert) override;
	int nverts() override { return 2 * samples * (samples + 1) ; }

	std::vector<int> face(int nface) override;
	int nfaces() override { return 4 * samples * samples - 1 ; }

	Vec2f uv(int nvert) override { return Vec2f(0, 0); }

	Vec3f normal(int nvert) override;
private:
	float radius;
	Vec3f o;
	const int samples;
	
	Vec3f calSample(int nvert);
};

