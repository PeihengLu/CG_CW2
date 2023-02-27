/*
 * Shape.h
 *
 */
#pragma 1
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

	//
	// Destructor (must be overriden in subclass)
	//
	virtual ~Shape(){};

	//
	// Shape abstract methods (to be implemented by subclasses)
	//
	virtual std::tuple<bool, Hit> intersect(Ray)=0;


protected:


};


} //namespace rt


#endif /* SHAPE_H_ */
