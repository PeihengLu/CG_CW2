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
		Hit h;

		// std::cout<<"ray direction: <"<<std::to_string(ray.rayDirection.x)<<"," <<std::to_string(ray.rayDirection.y) <<"," <<std::to_string(ray.rayDirection.z) << ">\n";
		// vector between the ray's origin and the sphere's center
		Vec3f sphere_vector = this->center - ray.origin;
		// projection from the sphere_vector onto the ray's direction
		float projection = sphere_vector.dotProduct(ray.rayDirection) / ray.rayDirection.norm();
		// ray does not point towards the sphere
		if (projection < 0) {
			// printf("camera pointing the wrong way\n");
			return std::make_tuple(false, h);
		}

		// distance from sphere's center to the projection point
		float distance = ((ray.origin + ray.rayDirection * projection) - this->center).norm();
		// std::cout<< "radius of sphere is: "<< std::to_string(this->radius) << std::endl;
		// std::cout << "distance to center is: " << std::to_string(distance) <<std::endl;
		if (distance > this->radius) {
			// printf("ray too far\n");
			return std::make_tuple(false, h);
		}
		// calculate interception point using trigonometry 
		Vec3f interception_point = ray.origin + ray.rayDirection * (projection - sqrt(pow(this->radius, 2) - pow(distance, 2)));
		h.distanceToOrigin = (interception_point - ray.origin).norm();
		// TODO update this for texture mapping
		h.material = this->material;
		h.point = interception_point;
		printf("hit");

		return std::make_tuple(true, h);
	}



} //namespace rt


