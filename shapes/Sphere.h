/*
 * Sphere.h
 *
 *
 */
#pragma 1
#ifndef SPHERE_H_
#define SPHERE_H_

#include "core/Shape.h"

namespace rt{

class Sphere:public Shape{

public:
	Vec3f const center;
	float const radius;
	Material* const material;

	//
	// Constructors
	//
	Sphere();
	Sphere(Vec3f center, float radius, Material * material);

	~Sphere();


	//
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	std::tuple<bool, Hit> intersect(Ray ray);

private:

};

} //namespace rt




#endif /* SPHERE_H_ */
