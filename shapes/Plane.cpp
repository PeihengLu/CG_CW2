/*
 * Plane.cpp
 *
 *
 */
#include "Plane.h"


namespace rt{
	Plane::Plane(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3, Material * material):v0(v0), v1(v1), v2(v2), v3(v3), Shape(material){}

	Plane* parsePlane(Value& planeSpecs, Material* material){
		Vec3f v0 = arrayToVec(planeSpecs["v0"]);
		Vec3f v1 = arrayToVec(planeSpecs["v1"]);
		Vec3f v2 = arrayToVec(planeSpecs["v2"]);
		Vec3f v3 = arrayToVec(planeSpecs["v3"]);
		return new Plane(v0, v1, v2, v3, material);
	}	

	/**
	 * Computes whether a ray hit the specific instance of a plane and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	std::tuple<bool, Hit> Plane::intersect(Ray ray){
        // whether there is a hit or not
        bool hit;
		Hit h;
		//-----------to be implemented -------------


		return std::make_tuple(hit, h);

	}



} //namespace rt


