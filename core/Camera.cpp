/*
 * Camera.cpp
 *
 */
#include <iostream>

#include "Camera.h"
#include "cameras/Pinhole.h"
#include "cameras/ThinLens.h"

namespace rt{

	Camera::~Camera(){};



/**
 * Factory function that returns camera subclass based on camera specifications
 *
 * @param cameraSpecs camera specifications json object
 *
 * @return camera subclass instance
 *
 */
Camera* Camera::createCamera(Value& cameraSpecs){

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
				arrayToVec(cameraSpecs["lookat"]),
				arrayToVec(cameraSpecs["up"]));

	}else if (cameraType.compare("thinlens")==0){
		return ;
	}

	return 0;

}

// added a helper function for converting JSON array to Vec3f
Vec3f arrayToVec(Value& arr){
    int i = 0;
    float* vec = new float[3];
    for (auto& v : arr.GetArray()){
        vec[i] = v.GetFloat();
        i++;
    }
    Vec3f *vector = new Vec3f(vec[0], vec[1], vec[2]);
    return *vector;
}




} //namespace rt
