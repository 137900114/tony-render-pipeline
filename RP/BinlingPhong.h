#pragma once
#include "config.h"
#include "Shader.h"

class BinlingPhong : public Shader {
	Vec3f worldPos[3];
	Camera* camera;
	Vec3f lightDir;
	Vec3f normal[3];


public:
	Vec3f vertex(Vec3f worldPos, Vec3f normal, Vec2f uv, int nvert) override;
	Color fragment(Vec3f bary) override;
	BinlingPhong(Camera* camera, Vec3f lightDir) :camera(camera), lightDir(lightDir),
		specular(1,1,1), diffus(1,1,1){}

	float Gross = 0.5f,lightIMax = 1.f,lightIMin = 0.3f;
	Vec3f specular;
	float specularPow = 0.3f;
	Vec3f diffus;
	
};