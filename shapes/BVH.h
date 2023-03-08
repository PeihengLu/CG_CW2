/*
 * BVH.h
 *
 *
 */

#ifndef BVH_H_
#define BVH_H_

#include "core/RayHitStructs.h"
#include "core/Shape.h"

namespace rt{


// a BVN node
class BVH: public Shape{
    public:
    BoundingBox* bbox;
    std::vector<Shape*> shapes;

    BVH* left;
    BVH* right;

    BVH(const std::vector<Shape*>& shapes);

	//
	// Shape abstract methods (to be implemented by subclasses)
	//
    std::tuple<bool, Hit> intersect(Ray ray);

	std::tuple<bool, Hit, Shape*> testIntersect(Ray ray);


    ~BVH(){
        if (left != nullptr) {
            delete left;
        }
        if (right != nullptr) {
            delete right;
        }
    };
};


} //namespace rt



#endif /* BVH_H_ */
