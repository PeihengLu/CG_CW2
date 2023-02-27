/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "rapidjson/document.h"
#include "math/geometry.h"


using namespace rapidjson;

namespace rt{

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

	//
	// Constructors
	//
	Camera(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up):height(height), width(width), fov(fov), position(position), lookat(lookat), up(up){};

	//
	// Destructor
	//
	virtual ~Camera();


	//
	// factory function : returns camera instance dynamically based on camera specifications
	//
	static Camera* createCamera(Value& cameraSpecs);


	//
	// print function (to be implemented by the subclasses )
	//
	virtual void printCamera()=0;



	//
	// other camera functions (to complete)
	//


	








protected:

	

};

} //namespace rt



#endif /* CAMERA_H_ */
