#pragma once
#include "geometry.h"
struct CameraDesc {
	Vec3f pos,center,up;
	struct ViewPort {
		int x, y, h, w, d;
	} ViewPort;
};


class Camera {
public:
	Camera(CameraDesc& desc):Trans(adaptTrans(desc)),setting(desc){}
	Camera(int height,int width,int depth) {
		setting = {Vec3f(0,0,0),Vec3f(0,0,1),Vec3f(0,1,0),
				   {0,0,height,width,depth} };
		Trans = Matrix4x4f(adaptTrans(setting));
	}
	CameraDesc getCurrentSetting() const{ return setting; }
	void applyNewSetting(CameraDesc desc) {
		setting = desc;
		Trans = adaptTrans(desc);
	}
	Vec3f worldToScreen(Vec3f vec) const;
private:
	static Matrix4x4f adaptTrans(CameraDesc desc);
	Matrix4x4f Trans;
	CameraDesc setting;
};