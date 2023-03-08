/*
 * Shape.h
 *
 */
#ifndef SHAPE_H_
#define SHAPE_H_

#include "core/RayHitStructs.h"
#include "core/Material.h"
#include "shapes/BoundingBox.h"


namespace rt{

enum ShapeType{
	SPHERE,
	PLANE,
	TRIANGLE
};

class Shape{
public:
	Material* const material;
    // texture related
	bool const textured;
	int const texture_width;
	int const texture_height;
	Vec3f* textures;
	ShapeType shapeType;

	//
	// Constructors
	//
	Shape();
	Shape(Material* material, ShapeType type);
	Shape(Material* material, ShapeType type, int const texture_width, int const texture_height, Vec3f* textures);

	//
	// Destructor (must be overriden in subclass)
	//
	virtual ~Shape(){};
	// returns the color of pixel to be used instead of diffuse color
	virtual Vec3f getTexture(Vec3f intersection);
	// create a bounding box for the shape
	virtual BoundingBox* getBoundingBox();

	//
	// Shape abstract methods (to be implemented by subclasses)
	//
	virtual std::tuple<bool, Hit> intersect(Ray)=0;


protected:


};

float pointToLineDist(Vec3f point, Vec3f v0, Vec3f v1);
BoundingBox* compute_bounding_box(const std::vector<Shape*>& shapes);
} //namespace rt


#endif /* SHAPE_H_ */
