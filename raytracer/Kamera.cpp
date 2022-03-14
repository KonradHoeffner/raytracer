#include "stdafx.h"
#include "Kamera.h"

Kamera::Kamera()
{
	 clippingNear = 0.01;
	 clippingFar = 1000;
//	 fovyGrad = 45;

	 position.set(0,0,5);
	 ziel.set(0,0,0);
	 oben.set(0,1,0);
}

Kamera::~Kamera()
{
}

Vector3d Kamera::getSichtVektor()
{
	Vector3d v  = ziel-position;
	v.normalize();
	return v;
}

Vector3d Kamera::getRechts()
{
	Vector3d v = oben.cross(getSichtVektor());
	v.normalize();
	return v;
}



//	return Vector3d(ziel.x-position.x,ziel.y-position.y,ziel.z-position.z);
