/*
 * Sphere.h
 *
 *
 */
#ifndef PLANE_H_
#define PLANE_H_

#include "core/Shape.h"

namespace rt{

class Plane: public Shape{

public:
    Vec3f const v1;
    Vec3f const v2;
    Vec3f const v3;
    Vec3f const v0;
	Vec3f const normal;

	//
	// Constructors
	//
	Plane();
	Plane(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3, Material * material);
	Plane(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3, Material * material, int const texture_width, int const texture_height, Vec3f* textures);
	

	Vec3f getTexture(Vec3f intersection);
	std::tuple<bool, Hit> intersect(Ray ray);
	// create a bounding box for the shape
	BoundingBox* getBoundingBox();
	void calculateBoundingBox();

	~Plane();

	

private:
	BoundingBox* bbox;

};


} //namespace rt




#endif /* SPHERE_H_ */
