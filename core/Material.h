/*
 * Material.h
 *
 */
#pragma 1

#ifndef MATERIAL_H_
#define MATERIAL_H_
#include <math/geometry.h>

namespace rt{

class Material{
public:
float const ks;
float const kd;
float const kr;
float const specularexponent;
Vec3f const diffusecolor;

Material(): ks(0), kd(0), kr(0), specularexponent(0), diffusecolor(*(new Vec3f(0, 0, 0))){};
Material(float ks, float kd, float kr, float specularexponent, Vec3f diffusecolor): ks(ks), kd(kd), kr(kr), specularexponent(specularexponent), diffusecolor(diffusecolor){}

private:


};


} //namespace rt



#endif /* MATERIAL_H_ */
