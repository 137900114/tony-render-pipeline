#pragma once
#include "config.h"
#include "Shader.h"


struct Draw {
	Draw(Image* image):image(image),height(image->get_height()),width(image->get_width())
	,zbuffer(image->get_height()* image->get_width(),- 1e10){
	}

	void line(int x0, int y0, int x1, int y1, const Color& color);
	void line(const Vec2i& start, const Vec2i& end, const Color& color) {
		line(start.x, start.y, end.x, end.y, color);
	}
	void area(int x0, int y0, int x1, int y1, const Color& color);
	void area(const Vec2i& leftB,const Vec2i& rightC,const Color& color) {
		area(leftB.x,leftB.y,rightC.x,rightC.y,color);
	}
	void triangle(Vec3i* pts,Shader* color);

	void drawCall(Drawable* drawable,Shader* shader);

	~Draw() { }
private:
	

	static Vec3f barycentric(const Vec3i* pts, Vec2f p);
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

	vector<float> zbuffer;
	union {
		struct {
			int height, width;
		};
		int edge[2];
	};
};


