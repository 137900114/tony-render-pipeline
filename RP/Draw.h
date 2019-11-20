#pragma once
#include "../..//Common/Image.h"
#include "Shader.h"
#include "..//..//Common/Drawable.h"

//绘制从x0,y0到x1,y1的直线

struct Draw {
	Draw(Image* image):image(image),height(image->get_height()),width(image->get_width()){
		zbuffer = new int[height * width];
		for (int i = 0; i != height * width; i++) {
			zbuffer[i] = std::numeric_limits<int>::min();
		}
	}

	void line(int x0, int y0, int x1, int y1, const Color& color);
	void line(const Vec2i& start, const Vec2i& end, const Color& color) {
		line(start.x, start.y, end.x, end.y, color);
	}
	void area(int x0, int y0, int x1, int y1, const Color& color);
	void area(const Vec2i& leftB,const Vec2i& rightC,const Color& color) {
		area(leftB.x,leftB.y,rightC.x,rightC.y,color);
	}
	

	void drawCall(Drawable* drawable,Shader* shader);

	~Draw() { delete[] zbuffer; }
private:
	static Vec3f barycentric(const Vec3i* pts, Vec2i p);
	void triangle(Vec3i* pts,Shader* color);

	inline int xytoz(int x,int y) {
		return x + y * width;
	}
	inline int xytoz(Vec2i i) {
		return xytoz(i.x,i.y);
	}
	inline Vec2i ztoxy(int i) {
		return Vec2i(i % width,i / width);
	}
	Image* image;

	int* zbuffer;
	union {
		struct {
			int height, width;
		};
		int edge[2];
	};
};


