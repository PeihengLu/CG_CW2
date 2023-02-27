/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "core/RayHitStructs.h"
#include "core/Material.h"

namespace rt{

class Shape{
public:

	//
	// Constructors
	//
	Shape();
	Shape(Material * mat): material(mat){};

	//
	// Destructor (must be overriden in subclass)
	//
	virtual ~Shape();

	//
	// Shape abstract methods (to be implemented by subclasses)
	//
	virtual std::tuple<bool, Hit> intersect(Ray)=0;


protected:

	Material * material;

};


} //namespace rt


#endif /* SHAPE_H_ */
