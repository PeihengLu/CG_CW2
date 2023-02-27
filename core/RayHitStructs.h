/*
 * RayHitStructs.h
 */
#pragma 1

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include <core/Material.h>

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
	// material of the interception point
	Material* material;
};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
