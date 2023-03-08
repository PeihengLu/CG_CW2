/*
 * ThinLens.cpp
 *
 *
 */
#include <iostream>
#include <random>

#include "ThinLens.h"




namespace rt{

	//
	// ThinLens constructor (example)
	//
	ThinLens::ThinLens(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up, float lensRadius, float focalDistance):Camera(width, height, fov, position, lookat, up), lensRadius(lensRadius), focalDistance(focalDistance){

		//to fill
		type = THINLENS;
		printf("thin lens camera created\n");

	}

	ThinLens::ThinLens(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up, float lensRadius, float focalDistance, int sampleNum):Camera(width, height, fov, position, lookat, up), lensRadius(lensRadius), focalDistance(focalDistance){
		this->sampleNum = sampleNum;
		//to fill
		type = THINLENS;
		printf("thin lens camera created\n");

	}

	Ray ThinLens::getCameraRay(int w, int h){
	// defining the camera primary ray from the camera position to the pixel position
		Ray cameraRay;
		cameraRay.raytype = PRIMARY;
		cameraRay.origin = this->position;
		float fovRadians = this->fov * M_PI / 180.0f;
		// half of the width and height of camera plane, make working with tan easier
		// distance from the camera to the image plane
		float distance = this->focalDistance;
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

	// std::vector<Ray> ThinLens::getCameraRaySamples(int w, int h) {
	// 	std::vector<Ray> cameraRays;
	// 	Vec3f lookat = this->lookat;
	// 	lookat = lookat.normalize();
	// 	Vec3f up = this->up;
	// 	up = up.normalize();
	// 	Vec3f right = lookat.crossProduct(up).normalize();
	// 	// Generate random samples in the circle's area
	// 	std::random_device rd;
	// 	std::mt19937 gen(rd());
	// 	std::uniform_real_distribution<> distributionRadius(0, lensRadius);
	// 	float radius_step = lensRadius / cbrt(sampleNum);
	// 	std::uniform_real_distribution<> dis_theta(0, 2*M_PI);
	// 	float theta_step = 2*M_PI / cbrt(sampleNum);
	// 	std::uniform_real_distribution<> dis_phi(-1, 1);
	// 	float phi_step = 2 / cbrt(sampleNum);
	// 	for (int i = 0; i < sampleNum; ++i) {
	// 		double r = sqrt(std::round(distributionRadius(gen) / radius_step) * radius_step);
	// 		double theta = std::round(dis_theta(gen) / theta_step) * theta_step;
	// 		double phi = asin(std::round(dis_phi(gen) / phi_step) * phi_step);
	// 		Vec3f samplePos = this->position + r * (cos(theta) * right + sin(theta) * up + phi * lookat);
			
	// 		Ray cameraRay;
	// 		cameraRay.raytype = PRIMARY;
	// 		cameraRay.origin = this->position;
	// 		float fovRadians = this->fov * M_PI / 180.0f;
	// 		// we use 4 as the estimated object distance
	// 		float distance = 1;
	// 		float halfWidth = distance * tan(fovRadians / 2.0f);
	// 		float halfHeight = this->height * halfWidth / this->width;
	// 		float imageX = ((2.0f * (w+0.5)) / this->width - 1.0f) * halfWidth;
	// 		float imageY = (1.0f - (2.0f * (h+0.5)) / this->height) * halfHeight;
	// 		Vec3f pixelLocation = this->position + lookat*distance + right*imageX + up*imageY;
			
	// 		cameraRay.rayDirection = (pixelLocation - cameraRay.origin).normalize();
	// 		// apply field of view 
	// 		Vec3f focalPoint = this->position + cameraRay.rayDirection * focalDistance;
	// 		cameraRay.rayDirection = (focalPoint - samplePos).normalize();
	// 		cameraRay.origin = samplePos;

	// 		cameraRays.push_back(cameraRay);
	// 	}

	// 	return cameraRays;
	// }

	std::vector<Ray> ThinLens::getCameraRaySamples(int w, int h) {
		std::vector<Ray> cameraRays;
		Vec3f lookat = this->lookat;
		lookat = lookat.normalize();
		Vec3f up = this->up;
		up = up.normalize();
		Vec3f right = lookat.crossProduct(up).normalize();
		// Generate random samples in the circle's area
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distributionRadius(0, lensRadius);
		float radius_step = lensRadius / cbrt(sampleNum);
		std::uniform_real_distribution<> dis_theta(0, 2*M_PI);
		float theta_step = 2*M_PI / cbrt(sampleNum);
		std::uniform_real_distribution<> dis_phi(-1, 1);
		float phi_step = 2 / cbrt(sampleNum);
		for (int i = 0; i < sampleNum; ++i) {
			double r = sqrt(std::round(distributionRadius(gen) / radius_step) * radius_step);
			double theta = std::round(dis_theta(gen) / theta_step) * theta_step;
			double phi = asin(std::round(dis_phi(gen) / phi_step) * phi_step);
			Vec3f samplePos = this->position + r * (cos(theta) * right + sin(theta) * up + phi * lookat);

			float jitterAmount = this->lensRadius / 20;

			// Jitter sample position
			std::uniform_real_distribution<> distributionJitter(-jitterAmount, jitterAmount);
			Vec3f jitter = distributionJitter(gen) * right + distributionJitter(gen) * up;
			samplePos = samplePos + jitter;

			while ((samplePos - this->position).length() > this->lensRadius) { // resample the jitter if outside of lens
				samplePos = samplePos - jitter;
				jitter = distributionJitter(gen) * right + distributionJitter(gen) * up;
				samplePos = samplePos + jitter;
			}

			Ray cameraRay;
			cameraRay.raytype = PRIMARY;
			cameraRay.origin = this->position;
			float fovRadians = this->fov * M_PI / 180.0f;
			// we use 4 as the estimated object distance
			float distance = 1;
			float halfWidth = distance * tan(fovRadians / 2.0f);
			float halfHeight = this->height * halfWidth / this->width;
			float imageX = ((2.0f * (w+0.5)) / this->width - 1.0f) * halfWidth;
			float imageY = (1.0f - (2.0f * (h+0.5)) / this->height) * halfHeight;
			Vec3f pixelLocation = this->position + lookat*distance + right*imageX + up*imageY;

			cameraRay.rayDirection = (pixelLocation - cameraRay.origin).normalize();
			// apply field of view 
			Vec3f focalPoint = this->position + cameraRay.rayDirection * focalDistance;
			cameraRay.rayDirection = (focalPoint - samplePos).normalize();
			cameraRay.origin = samplePos;

			cameraRays.push_back(cameraRay);
		}

    	return cameraRays;
	}

	

	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void ThinLens::printCamera(){
		printf("I am a thin lens camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
	}

} //namespace rt
