/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"

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
			if (camera->type == PINHOLE) {
				Ray cameraRay = camera->getCameraRay(w, h);
				// std::cout<<"camera ray direction: <"<<std::to_string(cameraRay.rayDirection.x)<<"," <<std::to_string(cameraRay.rayDirection.y) <<"," <<std::to_string(cameraRay.rayDirection.z) << ">\n";
				std::tuple<bool, Hit, Shape*> result = scene->testIntercept(cameraRay);
				bool cameraHit = std::get<0>(result);
				if (cameraHit){
					Hit hit = std::get<1>(result);
					Shape* shape = std::get<2>(result);

					for (LightSource* light: scene->getLightSources()) {
						pixelbuffer[w + h * camera->width] = pixelbuffer[w + h * camera->width] + getColorFromLight(hit, shape, light, scene, cameraRay.origin, 2);
					}

					pixelbuffer[w + h * camera->width].x = std::min(pixelbuffer[w + h * camera->width].x, 1.0f);
					pixelbuffer[w + h * camera->width].y = std::min(pixelbuffer[w + h * camera->width].y, 1.0f);
					pixelbuffer[w + h * camera->width].z = std::min(pixelbuffer[w + h * camera->width].z, 1.0f);
				} else {
					pixelbuffer[w + h * camera->width] = scene->getBGColor();
				}
			} else if (camera->type == THINLENS) {
				std::vector<Ray> rays = camera->getCameraRaySamples(w, h);
				int sampleNum = rays.size();

				for (Ray cameraRay: rays) {
					Vec3f c = Vec3f();
					std::tuple<bool, Hit, Shape*> result = scene->testIntercept(cameraRay);
					bool cameraHit = std::get<0>(result);
					
					if (cameraHit){
						Hit hit = std::get<1>(result);
						Shape* shape = std::get<2>(result);

						for (LightSource* light: scene->getLightSources()) {
							c = c + getColorFromLight(hit, shape, light, scene, cameraRay.origin, 2);
						}


						c.x = std::min(c.x, 1.0f);
						c.y = std::min(c.y, 1.0f);
						c.z = std::min(c.z, 1.0f);
					} else {
						c = scene->getBGColor();
					}
					c /= sampleNum;
					pixelbuffer[w + h * camera->width] = pixelbuffer[w + h * camera->width] + c;
				}
			}
		}
	}



	return pixelbuffer;
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


