#include "StdAfx.h"


int main(int argc, char* argv[])
{
	cout << "Raytracer: Main.cpp wird gestartet" << endl;
	//raytrace();

	Vector3d t1(12,43,45);
	Vector3d t2(34,31,21);
	Vector3d t3(6,123,3);

	Vector3d p1(-1,-1,0);
	p1.set(0,0,0);
	Vector3d p2(0,1,0);
	Vector3d p3(1,0,0);
	
	Vector3d l1(0,0,-1);
	Vector3d l2(1,0,1);
	Vector3d schnittPunkt(1,2,3);
	if(!IntersectPlaneLine(p1,p2,p3,l1,l2,schnittPunkt)) cout << "kein ";
	cout << "Schnittpunkt gefunden" << endl;
	schnittPunkt.print();

	return 0;
}