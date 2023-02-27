/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"


namespace rt{

	Sphere::Sphere():radius(0), material(nullptr){};
	Sphere::Sphere(Vec3f center, float radius, Material * material):center(center), radius(radius), material(material){};

	Sphere::~Sphere(){
		delete this->material;
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


