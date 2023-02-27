/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{
	Triangle::Triangle():material(nullptr){};
	Triangle::Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Material * material):v0(v0), v1(v1), v2(v2), material(material){};

	Triangle::~Triangle(){
		delete this->material;
		delete &(this->v0);
		delete &(this->v1);
		delete &(this->v2);
	}

    std::tuple<bool, Hit> Triangle::intersect(Ray ray){
		bool hit;
		Hit h;

        
		return std::make_tuple(hit, h);
	}



} //namespace rt
