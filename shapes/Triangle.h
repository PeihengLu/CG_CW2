/*
 * Triangle.h
 *
 *
 */
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"

namespace rt{



class Triangle: public Shape{

    public:
    Vec3f const v1;
    Vec3f const v2;
    Vec3f const v0;

    Triangle();
    Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Material * material);
    Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Material * material, int const texture_width, int const texture_height, Vec3f* textures);
    


    Vec3f getTexture(Vec3f intersection);
    // create a bounding box for the shape
	BoundingBox* getBoundingBox();
	void calculateBoundingBox();

    ~Triangle();
    

    std::tuple<bool, Hit> intersect(Ray ray);

    private:

    BoundingBox* bbox;


};

bool isPointInTriangle(Vec3f P, Vec3f A, Vec3f B, Vec3f C);


} //namespace rt




#endif /* TRIANGLE_H_ */
