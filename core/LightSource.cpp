/*
 * LightSource.cpp
 *
 */
#include "LightSource.h"
#include <lights/PointLight.h>
#include <lights/AreaLight.h>

namespace rt{


    LightSource* createLightSource(std::string type, Vec3f position, Vec3f is, Vec3f id) {
        // if (type.compare("pointlight")==0)
        printf("new light source created\n");
        // TODO test if intensity is handled correctly
        is /= 100.0f;
        return new PointLight(position, is, id);
    }

} //namespace rt

