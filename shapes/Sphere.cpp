/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"


namespace rt{

	Sphere::Sphere(Vec3f center, float radius, Material * material):center(center), radius(radius), Shape(material){};

	Sphere* parseSphere(Value& sphereSpecs, Material* material) {
		Vec3f center = arrayToVec(sphereSpecs["center"]);
		float radius = sphereSpecs["radius"].GetFloat();
		return new Sphere(center, radius, material);
	}


	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	std::tuple<bool, Hit> Sphere::intersect(Ray ray){
		bool hit;
		Hit h;

		return std::make_tuple(hit, h);
	}



} //namespace rt


