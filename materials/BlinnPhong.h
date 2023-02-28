/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "core/Material.h"
#include "core/Scene.h"
#include "core/Camera.h"
#include "core/Shape.h"
#include "core/RayHitStructs.h"


namespace rt{

class BlinnPhong: public Material{
    public:

    float const ks;
    float const kd;
    float const kr;
    float const specularexponent;
    Vec3f const diffusecolor;

    BlinnPhong();
    BlinnPhong(float ks, float kd, float kr, float specularexponent, Vec3f diffusecolor);
    BlinnPhong(Material* material, Vec3f colour);
    // no texture
    BlinnPhong(Material* material);

    Vec3f getColor(Scene* scene, LightSource* light, Camera* camera, Hit hit, const int nbounce);
};

Vec3f attenuate_id(Vec3f intensity, float distance);
Vec3f attenuate_is(Vec3f intensity, float distance);
Vec3f reflect(Vec3f in, Scene* scene, Camera* camera, Hit prevHit, const int nbounce);
Vec3f getColorFromLight(Hit hit, LightSource* light, Scene* scene, Camera* camera,const int nbounce);

} //namespace rt



#endif /* BLINNPHONG_H_ */
