/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "rapidjson/document.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include <vector>


using namespace rapidjson;

namespace rt{

enum CameraType {
	THINLENS,
	PINHOLE
};

class Camera{
public:
	//
	//camera members
	//
	int const height;
	int const width;
	int const fov; //field of view
	Vec3f const position;
	Vec3f const lookat;
	Vec3f const up;	
	Vec3f const right;
	CameraType type;


	//
	// Constructors
	//
	Camera(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up);
	virtual std::vector<Ray> getCameraRaySamples(int w, int h);

	virtual Ray getCameraRay(int w, int h);

	//
	// Destructor
	//
	virtual ~Camera();


	//
	// factory function : returns camera instance dynamically based on camera specifications
	//
	static Camera* createCamera(Value& cameraSpecs, int sampleNum);


	//
	// print function (to be implemented by the subclasses )
	//
	virtual void printCamera()=0;



	//
	// other camera functions (to complete)
	//


	








protected:

	

};
Vec3f arrayToVec(Value& arr);
} //namespace rt



#endif /* CAMERA_H_ */
