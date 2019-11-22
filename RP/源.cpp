#include "config.h"
#include "Draw.h"
#include "BinlingPhong.h"
#include "UtilShader.h"
#include "Sphere.h"
#include "Plane.h"
#include "ImageMASS.h"


const char* target_file = "RenderPics\\sphere.png";
int height = 1000;
int width = 1000;
const int MAXDEPTH = 255;



int main() {
	int temp;

	ImageMASS image(height,width);
	Draw d(&image);
	Drawable* sphere = new Sphere(Vec3f(0,1,2), 0.5, 72);
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

	BinlingPhong binshader(&camera, LightDir);
	binshader.diffus = Vec3f(174, 133, 127);
	binshader.lightIMax = 1;
	binshader.lightIMin = 0.5f;
	binshader.Gross = .02f;
	d.drawCall(sphere, &binshader);


	UtilShader shader(&camera,LightDir);
	shader.diffuse = Vec3f(173, 143, 137);
	d.drawCall(plane1,&shader);

	shader.diffuse = Vec3f(169,162,152);
	d.drawCall(plane2, &shader);

	shader.diffuse = Vec3f(54,44,55);
	d.drawCall(plane3, &shader);

	PNGImage png(width,height,RGBCOLOR);
	image.sample(&png);


	png.flip_vertically();
	png.save(target_file);
}