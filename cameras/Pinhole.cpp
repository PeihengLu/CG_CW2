/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

#include "Pinhole.h"



namespace rt{

	//
	// Pinhole constructor 
	//
	Pinhole::Pinhole(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up):Camera(width, height, fov, position, lookat, up){
		printf("pinhole camera created\n");
		type = PINHOLE;
	}


	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void Pinhole::printCamera(){
		printf("I am a pinhole camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
		std::cout<<"camera position: <"<<std::to_string(this->position.x)<<"," <<std::to_string(this->position.y) <<"," <<std::to_string(this->position.z) << ">\n";
		std::cout<<"camera looking at(normalized): <"<<std::to_string(this->lookat.x)<<"," <<std::to_string(this->lookat.y) <<"," <<std::to_string(this->lookat.z) << ">\n";
		std::cout<<"camera up(normalized): <"<<std::to_string(this->up.x)<<"," <<std::to_string(this->up.y) <<"," <<std::to_string(this->up.z) << ">\n";
	}

	Ray Pinhole::getCameraRay(int w, int h){
	// defining the camera primary ray from the camera position to the pixel position
		Ray cameraRay;
		cameraRay.raytype = PRIMARY;
		cameraRay.origin = this->position;
		float fovRadians = this->fov * M_PI / 180.0f;
		// half of the width and height of camera plane, make working with tan easier
		float distance = 1.0f;
		float halfWidth = distance * tan(fovRadians / 2.0f);
		float halfHeight = this->height * halfWidth / this->width;
		float imageX = ((2.0f * (w+0.5)) / this->width - 1.0f) * halfWidth;
		float imageY = (1.0f - (2.0f * (h+0.5)) / this->height) * halfHeight;
		Vec3f pixelLocation = this->position + this->lookat*distance + this->right*imageX + this->up*imageY;
		// std::cout<<std::to_string(this->lookat.norm())<<std::endl;
		// std::cout<<"pixel location: <"<<std::to_string(pixelLocation.x)<<"," <<std::to_string(pixelLocation.y) <<"," <<std::to_string(pixelLocation.z) << ">\n";
		cameraRay.rayDirection = (pixelLocation - cameraRay.origin).normalize();
		return cameraRay;
	}



} //namespace rt

