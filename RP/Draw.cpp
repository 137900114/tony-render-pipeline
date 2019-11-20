#include "Draw.h"


void Draw::line(int x0,int y0,int x1,int y1,const Color& color) {
#if defined(G_DEBUG)
	int px0 = x0, py0 = y0, px1 = x1, py1 = y1;         
#endif

	bool steep = false;
	if (abs(x1 - x0) < abs(y1 - y0)) {
		std::swap(x0,y0);
		std::swap(x1,y1);
		steep = true;
	}

	if (x0 - x1 > 0) {
		std::swap(x0,x1);
		std::swap(y0,y1);
	}
	else if(x0 == x1){
		return;
	}
	int dx = x1 - x0;
	int dy = abs(y1 - y0);
	int halfx = dx / 2;
	int deltay = y1 > y0 ? 1 : -1;
	int y = y0;
	int fy = 0;
	for (int x = x0; x != x1;x++) {
		if (steep) 
			image->set(y,x,color);
		else
			image->set(x,y,color);
		fy += dy;
		if (fy > halfx) {
			y += deltay,fy -= dx;
		}
	}
	
#if defined(G_DEBUG)
	printf("成功画线%d,%d,%d,%d\n",px0,py0,px1,py1);
#endif
}

void Draw::area(int x0, int y0, int x1, int y1, const Color& color) {
	if (x0 >= x1 || y0 >= y1) {
		printf("wanring clear area: x0,y0应该比x1,y1的坐标值小");
	}
	for (int x = x0; x != x1;x++) {
		for (int y = y0; y != y1;y++) {
			image->set(x,y,color);
		}
	}
#if defined(G_DEBUG)
	printf("成功覆盖区域%d,%d,%d,%d\n",x0,y0,x1,y1);
#endif
}


template<class t>
inline t max(t x, t y) { return x > y ? x : y; }

template<class t>
inline t min(t x, t y) { return x < y ? x : y; }


Vec3f Draw::barycentric(const Vec3i *pts,Vec2i p) {
	Vec3f n1(pts[1].x - pts[0].x, pts[2].x - pts[0].x, pts[0].x - p.x);
	Vec3f n2(pts[1].y - pts[0].y, pts[2].y - pts[0].y, pts[0].y - p.y);
	Vec3f n = cross(n1, n2);
	if (n.z == 0) return Vec3f(-1,-1,-1);
	return Vec3f(1.f - (n.x + n.y) / n.z, n.x / n.z, n.y / n.z);
}

void Draw::triangle(Vec3i* pts,Shader* shader) {
	Vec2i boundmin(clamp(pts[0].x,width - 1,0),clamp(pts[0].y,height - 1,0));
	Vec2i boundmax(clamp(pts[0].x,width - 1,0),clamp(pts[0].y,height - 1,0));
    int index_max = xytoz(width,height);

	for (int i = 1; i != 3;i++) {
		for (int j = 0; j != 2; j++) {
			boundmin[j] = clamp(min(boundmin[j],pts[i][j]),edge[j] - 1,0);
			boundmax[j] = clamp(max(boundmax[j],pts[i][j]),edge[j] - 1,0);
		}
	}
	for (int x = boundmin.x; x != boundmax.x; x++) {
		for (int y = boundmin.y; y != boundmax.y; y++) {
			Vec3f bary = barycentric(pts,Vec2i(x,y)),pos(0,0,0);
			Vec2f uv(0,0);
			if (bary[0] < 0 || bary[1] < 0 || bary[2] < 0) continue;
			int z = 0;
			for (int i = 0; i != 3; i++) {
				z += pts[i][2] * bary[i];
			}
			int index = xytoz(x, y);
			if (index < 0 || index > index_max || zbuffer[index] >= z) continue;
			zbuffer[xytoz(x, y)] = z;
			Color color = shader->fragment(bary);
			image->set(x,y,color);
		}
	}
}


//顺时针绕向的三角形朝向是正面
void Draw::drawCall(Drawable* drawable,Shader* shader) {
	for (int i = 0; i != drawable->nfaces(); i++) {
		std::vector<int> vertI = drawable->face(i);
		Vec3f worldPos[3];
		Vec3i screenPos[3];
		Vec3f normal;
		Vec2f uvs[3];
		for (int j = 0; j != 3; j++) {
			worldPos[j] = drawable->vert(vertI[j]);
			uvs[j] = drawable->uv(vertI[j]);
		}
		normal = cross(worldPos[0] - worldPos[1],worldPos[0] - worldPos[2]).normalize();
		for (int j = 0; j != 3; j++)
			screenPos[j] = shader->vertex(worldPos[j],normal,uvs[j]);
		triangle(screenPos,shader);
	}
}