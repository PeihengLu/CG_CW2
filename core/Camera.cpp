/*
 * Camera.cpp
 *
 */
#include <iostream>

#include "Camera.h"
#include "cameras/Pinhole.h"
#include "cameras/ThinLens.h"

namespace rt{

	Camera::Camera(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up):height(height), width(width), fov(fov), position(position), lookat(lookat), up(up), right((lookat.crossProduct(up)).normalize()){};

	Camera::~Camera(){};

	// to be overwritten
	Ray Camera::getCameraRay(int w, int h) {
		Ray ray;
		return ray;
	}

	std::vector<Ray> Camera::getCameraRaySamples(int w, int h) {
		return std::vector<Ray>{this->getCameraRay(w, h)};
	}



/**
 * Factory function that returns camera subclass based on camera specifications
 *
 * @param cameraSpecs camera specifications json object
 *
 * @return camera subclass instance
 *
 */
Camera* Camera::createCamera(Value& cameraSpecs, int sampleNum){

	//check if cameratype is defined

	if (!cameraSpecs.HasMember("type")){
		std::cerr<<"Camera type not specified"<<std::endl;
		exit(-1);
	}

	std::string cameraType=cameraSpecs["type"].GetString();

	//return camera object based on camera specs
	if (cameraType.compare("pinhole")==0){
		return new Pinhole(cameraSpecs["width"].GetInt(),
				cameraSpecs["height"].GetInt(),
				cameraSpecs["fov"].GetInt(),
				arrayToVec(cameraSpecs["position"]),
				arrayToVec(cameraSpecs["lookat"]).normalize(),
				arrayToVec(cameraSpecs["up"]).normalize());

	}else if (cameraType.compare("thinlens")==0){
		return new ThinLens(cameraSpecs["width"].GetInt(),
				cameraSpecs["height"].GetInt(),
				cameraSpecs["fov"].GetInt(),
				arrayToVec(cameraSpecs["position"]),
				arrayToVec(cameraSpecs["lookat"]),
				arrayToVec(cameraSpecs["up"]),
				cameraSpecs["lensRadius"].GetFloat(),
				cameraSpecs["focalDistance"].GetFloat(),
				sampleNum);
	}

	return 0;

}



} //namespace rt
