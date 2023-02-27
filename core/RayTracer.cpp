/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"
#include "RayHitStructs.h"

namespace rt{


/**
 * Performs ray tracing to render a photorealistic scene
 *
 * @param camera the camera viewing the scene
 * @param scene the scene to render, including objects and lightsources
 * @param nbounces the number of bounces to consider for raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces){

	Vec3f* pixelbuffer=new Vec3f[camera->width*camera->height];

	//----------main rendering function to be filled------

	// rendering the scene
	for (int w = 0; w < camera->width; w++) {
		for (int h = 0; h < camera->height; h++){
			Ray cameraRay = getCameraRay(camera, w, h);
			scene->testIntercept(cameraRay);
		}
	}



	return pixelbuffer;
}

Ray getCameraRay(Camera* camera, int w, int h){
	// defining the camera primary ray from the camera position to the pixel position
	Ray cameraRay;
	cameraRay.raytype = PRIMARY;
	cameraRay.origin = camera->position;
	float fovRadians = camera->fov * M_PI / 180.0f;
	// half of the width and height of camera plane, make working with tan easier
	float halfWidth = camera->width / 2.0f;
	float halfHeight = camera->height / 2.0f;
	// distance from the camera to the image plane
	float distance = halfWidth / tan(camera->fov / 2.0f);
	// calculate the right using lookat and up, useful for transforming pixel location
	Vec3f right = camera->lookat.crossProduct(camera->up).normalize();
	float imageX = ((2.0f * w) / camera->width - 1.0f) * halfWidth;
	float imageY = (1.0f - (2.0f * h) / camera->height) * halfHeight;
	Vec3f pixelLocation = camera->position + camera->lookat*distance + right*imageX + camera->up*imageY;
	cameraRay.rayDirection = (pixelLocation - cameraRay.origin).normalize();
	return cameraRay;
}

/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer){

	//---------tonemapping function to be filled--------





	return pixelbuffer;

}

std::tuple<bool, Vec3f> RayTracer::testIntersection(std::vector<Shape*> shapes){
	// TODO get all the Hit objects with the shapes and find the one closest to camera position

}



} //namespace rt


