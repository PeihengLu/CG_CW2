/*
 * LightSource.h
 *
 */
#pragma 1

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include <math/geometry.h>



namespace rt{

class LightSource{
public:
LightSource(){};
LightSource(Vec3f position, Vec3f is, Vec3f id):position(position), is(is), id(id){};


std::string const type;
Vec3f const position;
Vec3f const is;
Vec3f const id;

private:

};

LightSource* createLightSource(std::string type, Vec3f position, Vec3f is, Vec3f id); 


} //namespace rt



#endif /* LIGHTSOURCE_H_ */
