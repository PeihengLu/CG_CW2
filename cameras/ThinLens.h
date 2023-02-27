/*
 * ThinLens.h
 *
 */
#pragma 1

#ifndef THINLENS_H_
#define THINLENS_H_

#include "core/Camera.h"


namespace rt{

class ThinLens:public Camera{
public:

	//
	// Constructors
	//
	ThinLens(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up);

	//
	//Destructor
	//
	~ThinLens(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();

};



} //namespace rt




#endif /* THINLENS_H_ */
