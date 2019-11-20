#include "Camera.h"
Matrix4x4f lookAt(Vec3f pos, Vec3f center, Vec3f up) {
	Vec3f z = (center - pos).normalize();
	Vec3f x = cross(up, z).normalize();
	Vec3f y = cross(z, x).normalize();
	Matrix4x4f R, Tri;
	for (int i = 0; i != 3; i++) {
		//对单位正交矩阵M M-1 = M.T
		R[0][i] = x[i];
		R[1][i] = y[i];
		R[2][i] = z[i];
		Tri[i][i] = 1;
		Tri[i][3] = -pos[i];
	}
	R[3][3] = 1, Tri[3][3] = 1;
	return Tri * R;
}

Matrix4x4f ViewPort(int x, int y, int h, int w, int d) {
	float m[] = {
		w / 2.f,0      ,0      ,w / 2.f + x,
		0      ,h / 2.f,0      ,h / 2.f + y,
		0      ,0      ,d / 2.f,d / 2.f    ,
		0      ,0      ,0      ,1
	};
	return Matrix4x4f(m);
}

Matrix4x4f Projection(int c) {
	Matrix4x4f result = Matrix4x4f::E;
	result[3][2] = c;
	return result;
}


Vec3f Camera::worldToScreen(Vec3f pos) const{
	if (pos == Vec3f(0.118774, 0.725955, -0.596105))
		int i = 0;
	Vec4f trans = Trans * Vec4f(pos);
	return Vec3f(trans.xyz() / trans.a);
}

Matrix4x4f Camera::adaptTrans(CameraDesc desc) {
	Matrix4x4f projection = Projection(- 1.f / (desc.center - desc.pos).norm());
	Matrix4x4f viewPort = ViewPort(desc.ViewPort.x,desc.ViewPort.y,desc.ViewPort.h,desc.ViewPort.w,desc.ViewPort.d);
	Matrix4x4f worldToView = lookAt(desc.pos,desc.center,desc.up);
	//std::cout << projection << viewPort << worldToView;
	return viewPort *projection * worldToView;
}