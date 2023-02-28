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



} //namespace rt

