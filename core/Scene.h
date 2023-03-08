/*
 * Scene.h
 *
 */
#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"



#include "core/LightSource.h"
#include "core/Shape.h"
#include "shapes/BVH.h"
#include "shapes/Sphere.h"
#include "shapes/Plane.h"
#include "shapes/Triangle.h"


using namespace rapidjson;

namespace rt{
Vec3f arrayToVec(Value& arr);


class Scene {
public:

	Scene(){};

	void createScene(Value& scenespecs);
	std::tuple<bool, Hit, Shape*> testIntercept(Ray ray);

	Vec3f getBGColor();
	std::vector<LightSource*> getLightSources();

private:

	std::vector<LightSource*> lightSources;
	std::vector<Shape*> shapes;
	Vec3f backgroundColor;
	BVH* bvh_root;
};

Material* parseMaterial(Value& materialSpecs);
LightSource* parseLightSourcce(Value& lightSpecs);
Shape* parseShape(Value& shapeSpecs);
Plane* parsePlane(Value& planeSpecs, Material* material);
Triangle* parseTriangle(Value& triangleSpecs, Material* material);
Sphere* parseSphere(Value& sphereSpecs, Material* material);
} //namespace rt



#endif /* SCENE_H_ */
