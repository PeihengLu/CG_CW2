/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "Scene.h"
namespace rt{



class Triangle: public Shape{

    public:
    Vec3f const v1;
    Vec3f const v2;
    Vec3f const v0;
    Material* const material;

    Triangle():v0(0), v1(0), v2(0), material(new Material()){};
    Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Material * material);
    Triangle* parseTriangle(Value& triangleSpecs, Material* material);
    

    std::tuple<bool, Hit> intersect(Ray ray);


};



} //namespace rt




#endif /* TRIANGLE_H_ */
