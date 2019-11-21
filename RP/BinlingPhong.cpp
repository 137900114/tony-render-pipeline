#include "BinlingPhong.h"

Vec3i BinlingPhong::vertex(Vec3f worldPos,Vec3f normal,Vec2f uv,int nvert) {
	this->worldPos[nvert] = worldPos;
	this->normal[nvert] = normal;

	Vec3f screenPos = camera->worldToScreen(worldPos);
	return ftoi(screenPos);
}

Color BinlingPhong::fragment(Vec3f bary) {
	Vec3f worldPos(0,0,0),normal(0,0,0);
	for (int i = 0; i != 3; i++) {
		worldPos = worldPos + this->worldPos[i] * bary[i];
		normal = this->normal[i] * bary[i] + normal;
	}
	Vec3f viewDir = worldPos - camera->getCurrentSetting().pos;
	Vec3f half = ( this->lightDir - viewDir).normalize();
	normal = normal.normalize();

	Vec3f specular = this->specular * pow(clamp(half * normal),1 / Gross) * specularPow;
	Vec3f diffus = this->diffus * clamp(normal * this->lightDir , lightIMax,lightIMin);
	Vec3f result = clamp3f(specular + diffus,255,0);

	return Color(result[0],result[1],result[2],255);
}