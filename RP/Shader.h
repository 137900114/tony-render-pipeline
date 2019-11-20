#pragma once
#include "../../Common/geometry.h"
#include "..//..//Common/Image.h"

class Shader {
public:
	virtual Vec3i vertex(Vec3f pos,Vec3f normal,Vec2f uv) = 0;
	virtual Color fragment(Vec3f bar) = 0;
	virtual ~Shader() {}
};