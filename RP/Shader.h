#ifndef __SHADER_H__
#define __SHADER_H__
#include "config.h"

class Shader {
public:
	virtual Vec3f vertex(Vec3f pos,Vec3f normal,Vec2f uv,int nvert) = 0;
	virtual Color fragment(Vec3f bar) = 0;
	virtual ~Shader() {}
};

#endif