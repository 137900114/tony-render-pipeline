#include "config.h"
#include "Draw.h"
#include <windows.h>


const char* model_file = "Model\\african_head.obj";
const char* target_file = "RenderPics\\png_test.png";
int height = 1000;
int width = 1000;
const int MAXDEPTH = 255;

class TestShader : public Shader {
private:
	Vec3f normal;
	Camera* camera;
	Vec3f lightDir;
public:
	Vec3i  vertex(Vec3f worldPos,Vec3f normal,Vec2f uv) override;
	Color  fragment(Vec3f bary) override;
	TestShader(Camera* camera,Vec3f lightDir):camera(camera),lightDir(lightDir){}
};

Vec3i TestShader::vertex(Vec3f worldPos,Vec3f normal,Vec2f uv) {
	Vec3f result = camera->worldToScreen(worldPos);
	this->normal = normal;
	return Vec3i(result.x,result.y,result.z);
}

Color TestShader::fragment(Vec3f bary) {
	float intensity = lightDir * normal;
	intensity = clamp(intensity * 0.5f + 0.5f,1,0);
	return Color(255 * intensity,255 * intensity,255 * intensity,255);
}


int main() {
	PNGImage* image = new PNGImage(height,width,RGBCOLOR);
	Draw d(image);
	Drawable* model = new Model(model_file);
	Vec3f LightDir(1,1,1);
	
	d.area(Vec2i(0,0),Vec2i(1000,1000),BLACK);


	Camera camera(width,height,MAXDEPTH);

	CameraDesc desc = camera.getCurrentSetting();
	desc.center = Vec3f(0,0,3);
	camera.applyNewSetting(desc);

	TestShader* shader = new TestShader(&camera,LightDir);
	d.drawCall(model, shader);
	image->flip_vertically();
	image->save(target_file);

}