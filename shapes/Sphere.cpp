/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"


namespace rt{

	Sphere::Sphere():radius(0), Shape(nullptr, SPHERE){calculateBoundingBox();}
	Sphere::Sphere(Vec3f center, float radius, Material * material):center(center), radius(radius), Shape(material, SPHERE){calculateBoundingBox();}
	Sphere::Sphere(Vec3f center, float radius, Material * material, int const texture_width, int const texture_height, Vec3f* textures):center(center), radius(radius), Shape(material, SPHERE, texture_width, texture_height, textures){calculateBoundingBox();}
	
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

		if (!this->bbox->intersect(ray.origin, ray.rayDirection)) {
			return std::make_tuple(false, h);
		}

		// std::cout<<"ray direction: <"<<std::to_string(ray.rayDirection.x)<<"," <<std::to_string(ray.rayDirection.y) <<"," <<std::to_string(ray.rayDirection.z) << ">\n";
		// vector between the ray's origin and the sphere's center
		Vec3f sphere_vector = this->center - ray.origin;
		// projection from the sphere_vector onto the ray's direction
		float projection = sphere_vector.dotProduct(ray.rayDirection) / ray.rayDirection.length();
		// ray does not point towards the sphere
		if (projection < 0) {
			// printf("camera pointing the wrong way\n");
			return std::make_tuple(false, h);
		}

		// distance from sphere's center to the projection point
		float distance = (sphere_vector.crossProduct(ray.rayDirection)).length() / ray.rayDirection.length();
		// std::cout<< "radius of sphere is: "<< std::to_string(this->radius) << std::endl;
		// std::cout << "distance to center is: " << std::to_string(distance) <<std::endl;
		if (distance >= this->radius) {
			// printf("ray too far\n");
			return std::make_tuple(false, h);
		}
		// calculate interception point using trigonometry 
		Vec3f interception_point = ray.origin + (ray.rayDirection).normalize() * (projection - sqrt(this->radius*this->radius - distance*distance));
		h.distanceToOrigin = (interception_point - ray.origin).length();
		// std::cout<<"sphere primary ray distance to origin is : " << std::to_string(h.distanceToOrigin) << std::endl;

		// if (h.distanceToOrigin < 0.02 && ray.raytype == SHADOW) {
		// 	return std::make_tuple(false, h);
		// }
		h.point = interception_point;
		h.normal = (h.point - this->center).normalize();

		return std::make_tuple(true, h);
	}

	Vec3f Sphere::getTexture(Vec3f intersection) {
		// Calculate the texture coordinates of the intersection point
		float phi = acos((intersection.y - this->center.y) / this->radius);
		float theta = atan2(intersection.z - this->center.z, intersection.x - this->center.x);
		float u = 0.5f + (theta / (2.0f * M_PI));
		float v = phi / M_PI;

		int x = std::floor(u*this->texture_width);
		int y = std::floor(v*this->texture_height);

		x = std::min(x, this->texture_width - 1);
		y = std::min(y, this->texture_height - 1);
		x = std::max(x, 0);
		y = std::max(y, 0);

		return textures[x + y*this->texture_width];
	}

	// TODO to be overwritten
    BoundingBox* Sphere::getBoundingBox() {
        return bbox;
    }

	void Sphere::calculateBoundingBox() {
		Vec3f radius_vec(this->radius);
        Vec3f bbox_min = this->center - radius_vec;
        Vec3f bbox_max = this->center + radius_vec;
        bbox = new BoundingBox(bbox_min, bbox_max);
	}
} //namespace rt


