/*
 * ThinLens.h
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include "core/Camera.h"
#include <vector>

namespace rt{

class ThinLens:public Camera{
public:

	float const lensRadius;
	float const focalDistance;
	int sampleNum = 100;

	//
	// Constructors
	//
	ThinLens(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up, float lensRadius, float focalDistance);
	ThinLens(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up, float lensRadius, float focalDistance, int sampleNum);

	Ray getCameraRay(int w, int h);
	std::vector<Ray> getCameraRaySamples(int w, int h);
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
