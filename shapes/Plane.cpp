/*
 * Plane.cpp
 *
 *
 */
#include "Plane.h"


namespace rt{
	Plane::Plane():material(nullptr){};
	Plane::Plane(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3, Material * material):v0(v0), v1(v1), v2(v2), v3(v3), material(material),normal(((v1 - v0).crossProduct(v2 - v1)).normalize()){
		std::cout<<"normal of the plane is: <"<<std::to_string(normal.x)<<"," <<std::to_string(normal.y) <<"," <<std::to_string(normal.z) << ">\n";
	}

	Plane::~Plane(){
		delete this->material;
		delete &(this->v0);
		delete &(this->v1);
		delete &(this->v2);
		delete &(this->v3);
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
		// check if the ray and the plane is parallel
		if (std::abs(ray.rayDirection.dotProduct(this->normal)) < 0.0001f) {
			return std::make_tuple(false, h);
		}

		// check if the ray is poiting towards another direction
		float distance = (ray.origin - this->v0).dotProduct(this->normal) / std::abs(ray.rayDirection.dotProduct(this->normal));
		if (distance < 0) {
			return std::make_tuple(false, h);
		}

		// printf("check range\n");

		Vec3f intersection = ray.origin + ray.rayDirection * distance;
		// check if the intersection point is within bounds
		if ((intersection - this->v0).dotProduct(intersection - this->v2) > 0) 
			return std::make_tuple(false, h);
		
		hit = true;
		h.point = intersection;
		h.distanceToOrigin = (intersection - ray.origin).norm();
		// TODO update for texture
		h.material = this->material;

		std::cout<<"distance from intersection point to plane is :" << (intersection - this->v0).dotProduct(this->normal)<<std::endl;
		std::cout<<"intersection point is: <"<<std::to_string(intersection.x)<<"," <<std::to_string(intersection.y) <<"," <<std::to_string(intersection.z) << ">\n";

		printf("intersected with a plane\n");

		return std::make_tuple(hit, h);

	}



} //namespace rt


