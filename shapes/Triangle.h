/*
 * Triangle.h
 *
 *
 */
#pragma 1
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"
namespace rt{



class Triangle: public Shape{

    public:
    Vec3f const v1;
    Vec3f const v2;
    Vec3f const v0;
    Material* const material;

    Triangle():material(nullptr){};
    Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Material * material);
    

    std::tuple<bool, Hit> intersect(Ray ray);


};




} //namespace rt




#endif /* TRIANGLE_H_ */
