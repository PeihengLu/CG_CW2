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
	backgroundColor = arrayToVec(scenespecs["backgroundcolor"]);

	for (Value& light: scenespecs["lightsources"].GetArray()) {
		LightSource* l = parseLightSourcce(light);
		lightSources.push_back(l);
	}

	for (Value& shape: scenespecs["shapes"].GetArray()) {
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
	return LightSource::createLightSource(lightType, position, is, id);
}

Shape* parseShape(Value& shapeSpecs) {
	Value& mat = shapeSpecs["material"];
	Material* material = parseMaterial(mat);

	std::string type = shapeSpecs["type"].GetString();

	// TODO add support for triangle mesh

	if (type.compare("sphere")==0) {
		return ;
	} else if (type.compare("plane")) {
		return ;
	} else if (type.compare("triangle")) {
		return ;
	}
}


Material* parseMaterial(Value& materialSpecs){
	float ks = materialSpecs["ks"].GetFloat();
	float kd = materialSpecs["kd"].GetFloat();
	if (!materialSpecs.HasMember("kr")) {
		float kr = 0;
	}
	float kr = materialSpecs["kr"].GetFloat();
	int specularexponent = materialSpecs["specularexponent"].GetInt();
	Vec3f diffusecolor = arrayToVec(materialSpecs["diffusecolor"]);
	return new Material(ks, kd, kr, specularexponent, diffusecolor);
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
std::tuple<bool, Material*> Scene::testIntercept(Ray ray) {
	// minimum distance to the ray origin
	float minDistance = 100.0f;
	bool intercepted;
	Material* interceptionMat=nullptr;
	for (Shape* shape: this->shapes) {
		std::tuple<bool, Hit> result = shape->intersect(ray);
		if (std::get<0>(result)){
			intercepted = true;
			// only need to know if there is any inteception at all for shadow ray
			// saving resources
			if (ray.raytype==SHADOW) {
				break;
			}
			Hit hit = std::get<1>(result);
			if (minDistance > hit.distanceToOrigin) {
				minDistance = hit.distanceToOrigin;
				Vec3f color = hit.material.diffusecolor;
				interceptionMat = &(hit.material);
			}
		}
	}
	return std::make_tuple(intercepted, interceptionMat);
}

} //namespace rt
