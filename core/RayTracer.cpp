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

	for (int w = 0; w < camera->width; w++) {
		for (int h = 0; h < camera->height; h++){
			pixelbuffer[w + h * camera->width] = *(new Vec3f(0, 0, 0));
		}
	}
	printf("initialization complete\n");

	//----------main rendering function to be filled------

	// rendering the scene
	for (int w = 0; w < camera->width; w++) {
		for (int h = 0; h < camera->height; h++){
			Ray cameraRay = getCameraRay(camera, w, h);
			// std::cout<<"camera ray direction: <"<<std::to_string(cameraRay.rayDirection.x)<<"," <<std::to_string(cameraRay.rayDirection.y) <<"," <<std::to_string(cameraRay.rayDirection.z) << ">\n";
			std::tuple<bool, Hit> result = scene->testIntercept(cameraRay);
			bool cameraHit = std::get<0>(result);
			if (cameraHit){
				Hit hit = std::get<1>(result);
				for (LightSource* light: scene->getLightSources()) {
					Ray shadowRay;
					shadowRay.origin = hit.point;
					shadowRay.rayDirection = (light->position - hit.point).normalize();
					shadowRay.raytype = SHADOW;
					std::tuple<bool, Hit> shadowResult = scene->testIntercept(shadowRay);
					bool shadowHit = std::get<0>(shadowResult);
					if (shadowHit) { // if this point is in the shadow for this light source
						continue;
					} else {
						Vec3f intensity = light->is;

						intensity /= (hit.point - light->position).norm();
						intensity.x = std::min(intensity.x, 1.0f);
						intensity.y = std::min(intensity.y, 1.0f);
						intensity.z = std::min(intensity.z, 1.0f);
						// TODO add bling phong model
						pixelbuffer[w + h * camera->height] = pixelbuffer[w + h * camera->height] + hit.material->diffusecolor;
					}
				}
			} else {
				pixelbuffer[w + h * camera->width] = scene->getBGColor();
			}
		}
	}



	return pixelbuffer;
}

// TODO camera ray could be wrong
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
	float distance = halfWidth / tan(fovRadians / 2.0f);

	float imageX = ((2.0f * w) / camera->width - 1.0f) * halfWidth;
	float imageY = (1.0f - (2.0f * h) / camera->height) * halfHeight;
	Vec3f pixelLocation = camera->position + camera->lookat*distance + camera->right*imageX + camera->up*imageY;
	// std::cout<<"pixel location: <"<<std::to_string(pixelLocation.x)<<"," <<std::to_string(pixelLocation.y) <<"," <<std::to_string(pixelLocation.z) << ">\n";
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
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer, int width, int height){

	//---------tonemapping function to be filled--------
	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height; h++){
			pixelbuffer[w + h * width] = pixelbuffer[w + h * width] * 255;
		}
	}

	return pixelbuffer;

}




} //namespace rt


