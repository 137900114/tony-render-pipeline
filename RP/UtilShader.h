#pragma once
#include "config.h"
#include "Shader.h"

class UtilShader : public Shader {
private:
	Vec3f normal;
	Camera* camera;
	Vec3f lightDir;
public:
	Vec3i  vertex(Vec3f worldPos, Vec3f normal, Vec2f uv, int nvert) override;
	Color  fragment(Vec3f bary) override;
	UtilShader(Camera* camera, Vec3f lightDir) :camera(camera), lightDir(lightDir),
	diffuse(255,255,255){}

	UtilShader(Camera* camera, Vec3f lightDir,Vec3f diffuse):camera(camera),
	lightDir(lightDir),diffuse(diffuse){}

	Vec3f diffuse;
};