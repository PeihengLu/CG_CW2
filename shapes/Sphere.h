/*
 * Sphere.h
 *
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "Scene.h"

namespace rt{

class Sphere:public Shape{

public:
	Vec3f const center;
	float const radius;

	//
	// Constructors
	//
	Sphere(Vec3f center, float radius, Material * material);

	Sphere* parseSphere(Value& sphereSpecs);

	virtual ~Sphere();


	//
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	std::tuple<bool, Hit> intersect(Ray ray);

private:

};



} //namespace rt




#endif /* SPHERE_H_ */
