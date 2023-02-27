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


using namespace rapidjson;

namespace rt{
Vec3f arrayToVec(Value& arr);


class Scene {
public:

	Scene(){};

	void createScene(Value& scenespecs);
	std::tuple<bool, Material*> testIntercept(Ray ray);

private:

	std::vector<LightSource*> lightSources;
	std::vector<Shape*> shapes;
	Vec3f backgroundColor;

	Material* parseMaterial(Value& materialSpecs);
	LightSource* parseLightSourcce(Value& lightSpecs);
	Shape* parseShape(Value& shapeSpecs);

};

} //namespace rt



#endif /* SCENE_H_ */
