/*
 * BlinnPhong.cpp
 *
 *
 */

#include "BlinnPhong.h"



namespace rt{


    BlinnPhong::BlinnPhong(): ks(0), kd(0), kr(0), specularexponent(0){}

    BlinnPhong::BlinnPhong(float ks, float kd, float kr, float specularexponent, Vec3f diffusecolor): ks(ks), kd(kd), kr(kr), specularexponent(specularexponent), diffusecolor(diffusecolor){}

    BlinnPhong::BlinnPhong(Material* material, Vec3f color):ks(material->ks), kd(material->kd), kr(material->kr), specularexponent(material->specularexponent), diffusecolor(color){};

    BlinnPhong::BlinnPhong(Material* material):ks(material->ks), kd(material->kd), kr(material->kr), specularexponent(material->specularexponent), diffusecolor(material->diffusecolor){};

    Vec3f BlinnPhong::getColor(Scene* scene, LightSource* light, Vec3f cameraPos, Hit hit, Shape* shape, const int nbounce){
        if (nbounce == 0) {
            return Vec3f();
        }

        Vec3f id = attenuate_id(light->id, (hit.point - light->position).length());
        Vec3f is = attenuate_is(light->is, (hit.point - light->position).length());

        Vec3f color = Vec3f();
        Vec3f hitToCamera = (cameraPos - hit.point).normalize();
        Vec3f hitToLight = (light->position - hit.point).normalize();

        Vec3f diffuse = this->diffusecolor * std::max(hitToLight.dotProduct(hit.normal), 0.0f) * id * this->kd;
        color = color + diffuse;

        Vec3f specular = is * pow(std::max((hitToCamera + hitToLight).normalize().dotProduct(hit.normal), 0.0f), this->specularexponent) * this->ks;
        color = color + specular;

        if (shape->material->kr > 0) {
            Vec3f reflectionColor = reflect(-hitToCamera, scene, cameraPos, hit, shape, nbounce - 1);
            color = color + shape->material->kr * reflectionColor;
        } 

        color.x = std::min(color.x, 1.0f);
        color.y = std::min(color.y, 1.0f);
        color.z = std::min(color.z, 1.0f);
        return color;
    }

    Vec3f attenuate_id(Vec3f intensity, float distance){
        intensity /= (4*M_PI*distance*distance + distance);
        // caps the intensity off at 1
        // intensity.x = std::min(intensity.x, 1.0f);
        // intensity.y = std::min(intensity.y, 1.0f);
        // intensity.z = std::min(intensity.z, 1.0f);
        return intensity;
    }

    Vec3f attenuate_is(Vec3f intensity, float distance){
        intensity /= (4*M_PI*distance*distance+ distance);
        intensity.x = std::min(intensity.x, 1.0f);
        intensity.y = std::min(intensity.y, 1.0f);
        intensity.z = std::min(intensity.z, 1.0f);
        return intensity;
    }

Vec3f reflect(Vec3f in, Scene* scene, Vec3f cameraPos, Hit prevHit, Shape* prevShape, const int nbounce) {
	Vec3f color = Vec3f(0, 0, 0);

	if (nbounce == 0) {
		return color;
	}

	in = in.normalize();
	
	Vec3f reflectionDir = (in - 2 * (in.dotProduct(prevHit.normal)) * prevHit.normal).normalize();

	Ray reflectionRay;
	reflectionRay.raytype = SECONDARY;
	reflectionRay.origin = prevHit.point;
	reflectionRay.rayDirection = reflectionDir;
	
	std::tuple<bool, Hit, Shape*> reflectResult = scene->testIntercept(reflectionRay);

	if (!std::get<0>(reflectResult)) {
		return color;
	}

	Hit hit = std::get<1>(reflectResult);
    Shape* shape = std::get<2>(reflectResult);

	for (LightSource* light: scene->getLightSources()) {
		color = color + getColorFromLight(hit, shape, light, scene, cameraPos, nbounce);
	}
    // TODO may be wrong
	return color * prevShape->material->kr;
}

Vec3f getColorFromLight(Hit hit, Shape* shape, LightSource* light, Scene* scene, Vec3f cameraPos, const int nbounce){
	Vec3f color;
	Ray shadowRay;
	shadowRay.origin = hit.point;
	shadowRay.rayDirection = (light->position - hit.point).normalize();
	shadowRay.raytype = SHADOW;
	std::tuple<bool, Hit, Shape*> shadowResult = scene->testIntercept(shadowRay);
	bool shadowHit = std::get<0>(shadowResult);
	if (shadowHit) { // if this point is in the shadow for this light source
		color = Vec3f(0, 0, 0);
	} else {
        BlinnPhong* shading;
		// TODO texture needs to be handled later
        if (shape->textured) {
            Vec3f color = shape->getTexture(hit.point);
            shading = new BlinnPhong(shape->material, color);
        } else {
            shading = new BlinnPhong(shape->material);
        }
		
		color = color  + shading->getColor(scene, light, cameraPos, hit, shape, nbounce);
		delete shading;
	}
	return color;
}

} //namespace rt
