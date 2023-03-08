/*
 * RayHitStructs.h
 */
#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include <math/geometry.h>

namespace rt{

/*
 * Ray structure definition
 */
enum RayType {PRIMARY, SECONDARY, SHADOW};

struct Ray{

	RayType raytype;

	//----------Ray variables to be filled------
	Vec3f rayDirection;
	Vec3f origin;
};


struct Hit{
	Vec3f point; //point where ray hits a shape
	//----------Hit variables to be filled------
	float distanceToOrigin;
	// surface normal of point of intersection
	Vec3f normal;
};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
