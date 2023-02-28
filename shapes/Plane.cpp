/*
 * Plane.cpp
 *
 *
 */
#include "Plane.h"


namespace rt{
	Plane::Plane():material(nullptr){};
	Plane::Plane(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3, Material * material):v0(v0), v1(v1), v2(v2), v3(v3), material(material), normal(((this->v0 - this->v1).crossProduct(this->v2 - this->v1)).normalize()){}

	Plane::~Plane(){}


	/**
	 * Computes whether a ray hit the specific instance of a plane and returns the hit data
	 * A square is simply two triangles pieced
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	std::tuple<bool, Hit> Plane::intersect(Ray ray){
		Hit h;

		// distance from ray origin to plane
		float distance = ray.rayDirection.dotProduct(this->normal);
		if (std::abs(distance) < 0.0001f) {
			return std::make_tuple(false, h);
		}

		// how much the ray should be extended or shrinked to reach the plane
		float length = std::abs((this->v0 - ray.origin).dotProduct(this->normal) / distance);
		
		Vec3f intersection = ray.origin + length * ray.rayDirection;

		// check if the intersection is actually on the plane(the camera ray is pointing towards the correc direction)
		if (std::abs((intersection - this->v0).dotProduct(this->normal)) > 0.0001f) {
			return std::make_tuple(false, h);
		}

		// if the ray's origin is on the plane, it will not intersect the plane
		if ((intersection - ray.origin).norm() < 0.001f) {
			return std::make_tuple(false, h);
		}

		// check intersection in square
		Vec3f edge0 = this->v1 - this->v0;
		Vec3f point_to_v0 = intersection - this->v0;
		Vec3f edge1 = this->v2 - this->v1;
		Vec3f point_to_v1 = intersection - this->v1;
		Vec3f edge2 = this->v3 - this->v2;
		Vec3f point_to_v2 = intersection - this->v2;
		Vec3f edge3 = this->v0 - this->v3;
		Vec3f point_to_v3 = intersection - this->v3;
		bool point_in_square =  (point_to_v0).dotProduct(edge0) >= 0;
		point_in_square =  point_in_square && (point_to_v1).dotProduct(edge1) >= 0;
		point_in_square =  point_in_square && (point_to_v2).dotProduct(edge2) >= 0;
		point_in_square =  point_in_square && (point_to_v3).dotProduct(edge3) >= 0;

		if (point_in_square) {
			if (ray.raytype == SHADOW) {
				return std::make_tuple(true, h);
			}
			h.point = intersection;
			float distance = (intersection - ray.origin).norm();
			h.distanceToOrigin = distance;
		 	// TODO update for texture mapping
		 	h.material = this->material;
			h.normal = this->normal;

			return std::make_tuple(true, h);
		}

		return std::make_tuple(false, h);
	}



} //namespace rt


