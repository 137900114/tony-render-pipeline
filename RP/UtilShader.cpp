#include "UtilShader.h"

Vec3i UtilShader::vertex(Vec3f worldPos, Vec3f normal, Vec2f uv, int nvert) {
	Vec3f result = camera->worldToScreen(worldPos);
	this->normal = normal;
	return Vec3i(result.x, result.y, result.z);
}

Color UtilShader::fragment(Vec3f bary) {
	float intensity = lightDir * normal;
	intensity = clamp(intensity * 0.5f + 0.5f, 1, 0);
	return Color(diffuse * intensity);
}
