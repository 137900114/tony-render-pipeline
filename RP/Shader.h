#ifndef __SHADER_H__
#define __SHADER_H__
#include "config.h"

class Shader {
public:
	virtual Vec3i vertex(Vec3f pos,Vec3f normal,Vec2f uv) = 0;
	virtual Color fragment(Vec3f bar) = 0;
	virtual ~Shader() {}
};

#endif