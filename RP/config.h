#pragma once
//#define G_DEBUG

#include "../Common/Image.h"
#include "../Common/geometry.h"
#include "../Common/Model.h"
#include "../Common/Camera.h"
#include "../Common/PNGImage.h"
#include <iostream>
using namespace std;

const Color WIHTE = {255,255,255,255};
const Color RED = { 255,0,0,255 };
const Color GREEN = { 0,225,0,255 };
const Color BLUE = { 0,0,255,255 };
const Color BLACK = { 0,0,0,255 };

inline Vec4f ColorToVec4f(Color c) {
	return Vec4f(c.r,c.g,c.b,c.a) / 255.f;
}

inline Color VecToColor(Vec4f vec) {
	vec = vec * 255;
	return Color(vec.x,vec.y,vec.z,vec.a);
}