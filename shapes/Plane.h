/*
 * Sphere.h
 *
 *
 */
#pragma 1
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
	Material* const material;

	//
	// Constructors
	//
	Plane();
	Plane(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3, Material * material);
	

	~Plane();

	std::tuple<bool, Hit> intersect(Ray ray);

private:

};


} //namespace rt




#endif /* SPHERE_H_ */
