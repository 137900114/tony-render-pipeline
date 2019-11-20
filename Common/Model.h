  
#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"
#include "Drawable.h"

class Model : public Drawable {
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<int> > faces_;
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	void setVert(int i,Vec3f vec);
	std::vector<int> face(int idx);
	Vec2f uv(int index) override;
};



#endif //__MODEL_H__