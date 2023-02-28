/*
 * Shape.h
 *
 */
#pragma 1
#ifndef SHAPE_H_
#define SHAPE_H_

#include "core/RayHitStructs.h"
#include "core/Material.h"
#include <vector>


namespace rt{

class Shape{
public:
	Material* const material;
    // texture related
	bool const textured;
	int const texture_width;
	int const texture_height;
	std::vector<Vec3f*> textures;
	std::string shapeType;

	//
	// Constructors
	//
	Shape():material(nullptr), textured(false), texture_height(0), texture_width(0){};
	Shape(Material* material, std::string type):material(material), textured(false), texture_height(0), texture_width(0), shapeType(type){};

	//
	// Destructor (must be overriden in subclass)
	//
	virtual ~Shape(){};
	// returns the color of pixel to be used instead of diffuse color
	virtual Vec3f getTexture(Vec3f intersection);

	//
	// Shape abstract methods (to be implemented by subclasses)
	//
	virtual std::tuple<bool, Hit> intersect(Ray)=0;


protected:


};


} //namespace rt


#endif /* SHAPE_H_ */
