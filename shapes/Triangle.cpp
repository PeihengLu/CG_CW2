/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{
	Triangle::Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Material * material):v0(v0), v1(v1), v2(v2), material(material){};

	Triangle* parseTriangle(Value& triangleSpecs, Material* material){
		Vec3f v0 = arrayToVec(triangleSpecs["v0"]);
		Vec3f v1 = arrayToVec(triangleSpecs["v1"]);
		Vec3f v2 = arrayToVec(triangleSpecs["v2"]);
		Vec3f v3 = arrayToVec(triangleSpecs["v3"]);
		return new Triangle(v0, v1, v2, material);
	}	

    std::tuple<bool, Hit> Triangle::intersect(Ray ray){
		bool hit;
		Hit h;

        
		return std::make_tuple(hit, h);
	}



} //namespace rt
