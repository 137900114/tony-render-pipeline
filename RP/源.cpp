#include "config.h"
#include "Draw.h"
#include "BinlingPhong.h"
#include "UtilShader.h"
#include "Sphere.h"
#include "Plane.h"
#include "ImageMASS.h"


const char* target_file = "sphere.png";
int height = 500;
int width = 500;
const int MAXDEPTH = 255;

class ColorShader : public Shader {
public:
	ColorShader(Vec4f color,Camera* c) :color(color),c(c) {}

	virtual Vec3f vertex(Vec3f pos, Vec3f normal, Vec2f uv, int nvert) override {
		return c->worldToScreen(pos);
	}
	virtual Color fragment(Vec3f bar) override {
		return VecToColor(color);
	}
	Vec4f color;
	Camera* c;
};


int main() {
	int temp;



	ImageMASS image(height,width);
	Draw d(&image);
	Drawable* sphere = new Sphere(Vec3f(0,0,2), 0.5, 72);
	Drawable* plane1 = new Plane(Vec3f(-10,10,10),Vec3f(0,10,0),Vec3f(0,0,0));
	Drawable* plane2 = new Plane(Vec3f(10, 10, 10), Vec3f(0, 10, 0), Vec3f(0, 0, 0));
	Drawable* plane3 = new Plane(Vec3f(-10, 0 ,10), Vec3f(0, 0, 0), Vec3f(10, 0, 10));

	Vec3f LightDir(0, 1, 1);
	LightDir = LightDir.normalize();

	d.area(Vec2i(0, 0), Vec2i(image.get_width(),image.get_height()), BLACK);

	Camera camera(image.get_width(), image.get_height(), MAXDEPTH);

	CameraDesc desc = camera.getCurrentSetting();
	desc.pos = Vec3f(0, 4, 8);
	camera.applyNewSetting(desc);


	UtilShader shader(&camera,LightDir);
	shader.diffuse = Vec3f(1,1,1);
	d.drawCall(plane1,&shader);

	shader.diffuse = Vec3f(1,1,1);
	d.drawCall(plane2, &shader);

	shader.diffuse = Vec3f(1,1,1);
	d.drawCall(plane3, &shader);
	
	shader.diffuse = Vec3f(0.6,0.5,0.7);
	d.drawCall(sphere, &shader);

	//Vec3i pts[] = { Vec3i(0,0,1),Vec3i(100,400,5),Vec3i(400,100,5) };
	//Vec3i pts1[] = { Vec3i(100,100,4),Vec3i(150,500,3),Vec3i(500,150,3) };
	//d.triangle(pts, &ColorShader(Vec4f(1, 0, 0, 1)));
	//d.triangle(pts1, &ColorShader(Vec4f(0, 0, 1, 1)));

	PNGImage png(width, height, RGBCOLOR);
	image.sample(&png);

	png.flip_vertically();
	png.save(target_file);
}