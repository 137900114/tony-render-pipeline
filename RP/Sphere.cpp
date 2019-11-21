#include "Sphere.h"

Vec3f Sphere::vert(int nvert) {
	return calSample(nvert) * radius + o;
}

std::vector<int> Sphere::face(int nface) {
	int u = nface / (samples * 4);
	int v = (nface / 2) % (samples * 2);

	int v0 = u * 2 * samples + v,v1,v2;
	if (nface % 2) {
		v1 = (u + 1) * 2 * samples + v + 1;
		v2 = v1 - 1;
	}
	else {
		v1 = v0 + 1;
		v2 = (u + 1) * 2 * samples + v + 1;
	}

	std::vector<int> result = {v0,v1,v2};
	return result;
}

Vec3f Sphere::normal(int nvert) {
	return calSample(nvert);
}

Vec3f Sphere::calSample(int nvert) {
	if (nvert >= nverts() || nvert < 0) {
		std::cerr << "sphere.calSample : number of the vert is " << nvert << " invaild" <<
			", which must be smaller than " << nverts() << endl;
		return Vec3f(0, 0, 0);
	}
	else if (nvert < 2 * samples) {
		return Vec3f(0, 1, 0);
	}
	else if (nvert >= 2 * samples * samples) {
		return o + Vec3f(0, -1, 0);
	}
	float theta = PI / samples;
	int u = nvert / (samples * 2);
	int v = nvert % (samples * 2);

	float y = cos(theta * u);
	float x = sin(theta * u) * cos(v * theta) ;
	float z = sin(theta * u) * sin(theta * v);

	return Vec3f(x, y, z).normalize();
}