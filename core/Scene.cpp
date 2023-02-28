/*
 * Scene.cpp
 *
 */
#include "Scene.h"



namespace rt{

/**
 * Parses json scene object to generate scene to render
 *
 * @param scenespecs the json scene specificatioon
 */
void Scene::createScene(Value& scenespecs){

	//----------parse json object to populate scene-----------
	// initialize the scene with different shapes
	printf("Start creating scene\n");
	backgroundColor = arrayToVec(scenespecs["backgroundcolor"]);
	printf("retrieved background colour\n");

	for (Value& light: scenespecs["lightsources"].GetArray()) {
		LightSource* l = parseLightSourcce(light);
		lightSources.push_back(l);
	}

	printf("Created all light sources\n");

	for (Value& shape: scenespecs["shapes"].GetArray()) {
		printf("parse a shape\n");
		Shape* s = parseShape(shape);
		shapes.push_back(s);
	}
}

LightSource* parseLightSourcce(Value& lightSpecs) {
	std::string lightType=lightSpecs["type"].GetString();

	// TODO implement switching between point light and area light
	Vec3f position = arrayToVec(lightSpecs["position"]);
	Vec3f is = arrayToVec(lightSpecs["is"]);
	Vec3f id = arrayToVec(lightSpecs["id"]);

	printf("Created light\n");
	return createLightSource(lightType, position, is, id);
}

Shape* parseShape(Value& shapeSpecs) {
	Value& mat = shapeSpecs["material"];
	Material* material = parseMaterial(mat);

	std::string type = shapeSpecs["type"].GetString();

	// TODO add support for triangle mesh
	if (type.compare("sphere")==0) {
		return parseSphere(shapeSpecs, material);
	} else if (type.compare("plane")==0) {
		return parsePlane(shapeSpecs, material);
	} else if (type.compare("triangle")==0) {
		return parseTriangle(shapeSpecs, material);
	}
}


Material* parseMaterial(Value& materialSpecs){
	printf("parsing a material\n");
	float ks = materialSpecs["ks"].GetFloat();
	float kd = materialSpecs["kd"].GetFloat();
	float kr;
	if (!materialSpecs.HasMember("kr")) {
		kr = 0;
	} else {
		kr = materialSpecs["kr"].GetFloat();
	}
	printf("loaded ks, kd, kr\n");
	int specularexponent = materialSpecs["specularexponent"].GetInt();
	Vec3f diffusecolor = arrayToVec(materialSpecs["diffusecolor"]);
	return new Material(ks, kd, kr, specularexponent, diffusecolor);
}

Sphere* parseSphere(Value& sphereSpecs, Material* material) {
	Vec3f center = arrayToVec(sphereSpecs["center"]);
	float radius = sphereSpecs["radius"].GetFloat();
	printf("created new sphere\n");
	return new Sphere(center, radius, material);
}

Triangle* parseTriangle(Value& triangleSpecs, Material* material){
	Vec3f v0 = arrayToVec(triangleSpecs["v0"]);
	Vec3f v1 = arrayToVec(triangleSpecs["v1"]);
	Vec3f v2 = arrayToVec(triangleSpecs["v2"]);
	printf("created new triangle\n");
	return new Triangle(v0, v1, v2, material);
}	

Plane* parsePlane(Value& planeSpecs, Material* material){
	Vec3f v0 = arrayToVec(planeSpecs["v0"]);
	Vec3f v1 = arrayToVec(planeSpecs["v1"]);
	Vec3f v2 = arrayToVec(planeSpecs["v2"]);
	Vec3f v3 = arrayToVec(planeSpecs["v3"]);
	printf("created new plane\n");
	return new Plane(v0, v1, v2, v3, material);
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

// testing the intersept with all 
std::tuple<bool, Hit> Scene::testIntercept(Ray ray) {
	// minimum distance to the ray origin
	// TODO change this to -1 and make some more changes to function utilizing this
	float minDistance = 1000000.0f;
	bool intercepted = false;
	Hit interception;
	for (Shape* shape: this->shapes) {
		std::tuple<bool, Hit> result = shape->intersect(ray);
		if (std::get<0>(result)){
			intercepted = true;
			// only need to know if there is any inteception at all for shadow ray
			// saving resources
			if (ray.raytype==SHADOW) {
				return std::make_tuple(true, interception);
			}
			Hit hit = std::get<1>(result);
			if (minDistance > hit.distanceToOrigin) {
				minDistance = hit.distanceToOrigin;
				interception = hit;
			}
		}
	}
	return std::make_tuple(intercepted, interception);
}

// getters
Vec3f Scene::getBGColor(){
	return this->backgroundColor;
}

std::vector<LightSource*> Scene::getLightSources(){
	return this->lightSources;
}

} //namespace rt
