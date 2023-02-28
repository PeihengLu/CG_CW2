/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{
	Triangle::Triangle():Shape(nullptr, "Triangle"){};
	Triangle::Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Material * material):v0(v0), v1(v1), v2(v2), Shape(material, "Triangle"){};

	Triangle::~Triangle(){
		delete this->material;
		delete &(this->v0);
		delete &(this->v1);
		delete &(this->v2);
	}

    std::tuple<bool, Hit> Triangle::intersect(Ray ray){
		Hit h;

		Vec3f normal = ((this->v1 - this->v0).crossProduct(this->v2 - this->v0)).normalize();

		// distance from ray origin to plane
		float distance = ray.rayDirection.dotProduct(normal);
		if (std::abs(distance) < 0.0001f) {
			return std::make_tuple(false, h);
		}

		// how much the ray should be extended or shrinked to reach the plane
		float length = std::abs((this->v0 - ray.origin).dotProduct(normal) / distance);
		
		Vec3f intersection = ray.origin + length * ray.rayDirection;

		// check if the intersection is actually on the plane(the camera ray is pointing towards the correc direction)
		if (std::abs((intersection - this->v0).dotProduct(normal)) > 0.0001f) {
			return std::make_tuple(false, h);
		}

		// if the ray's origin is on the plane, it will not intersect the plane
		if ((intersection - ray.origin).norm() < 0.001f && ray.raytype == SHADOW) {
			return std::make_tuple(false, h);
		}

		bool point_in_triangle = isPointInTriangle(intersection, this->v0, this->v1, this->v2);

		if (point_in_triangle) {
			if (ray.raytype == SHADOW) {
				return std::make_tuple(true, h);
			}
			h.point = intersection;
			float distance = (intersection - ray.origin).norm();
			h.distanceToOrigin = distance;
		// 	// TODO update for texture mapping
		 	h.shape = this;
			h.normal = normal;

			return std::make_tuple(true, h);
		}

		return std::make_tuple(false, h);
	}

	bool isPointInTriangle(Vec3f P, Vec3f A, Vec3f B, Vec3f C) {
		Vec3f AB = B - A;
		Vec3f AC = C - A;
		Vec3f AP = P - A;
		float dotABAB = AB.dotProduct(AB);
		float dotABAC = AB.dotProduct(AC);
		float dotABAP = AB.dotProduct(AP);
		float dotACAC = AC.dotProduct(AC);
		float dotACAP = AC.dotProduct(AP); 
		float denominator = dotABAB * dotACAC - dotABAC * dotABAC;
		float u = (dotACAC * dotABAP - dotABAC * dotACAP) / denominator;
		float v = (dotABAB * dotACAP - dotABAC * dotABAP) / denominator;
		return u >= 0 && v >= 0 && u + v <= 1;
	}


} //namespace rt
