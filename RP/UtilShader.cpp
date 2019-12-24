#include "UtilShader.h"

Vec3f UtilShader::vertex(Vec3f worldPos, Vec3f normal, Vec2f uv, int nvert) {
	Vec3f result = camera->worldToScreen(worldPos);
	this->normal = normal;
	return result;
}

Color UtilShader::fragment(Vec3f bary) {
	float intensity = lightDir * normal;
	intensity = clamp(intensity * 0.5f + 0.5f, 1, 0);
	Vec4f color(diffuse * intensity);
	return VecToColor(color);
}
