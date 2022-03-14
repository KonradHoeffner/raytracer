/* Verantwortlicher : Konrad
 * Beschreibung: Datenhaltungsklasse für ein dreieckiges Polygon 
*/
#ifndef DREIECK_H_
#define DREIECK_H_

#include "stdafx.h"

class Dreieck
{
public:

	// Punkte
	Vector3d p1,p2,p3;
	// Normalen
	Vector3d n1,n2,n3;
	
	Material* material;

	Dreieck();
	Dreieck(Vector3d p1,Vector3d p2,Vector3d p3);
	Dreieck(Vector3d p1,Vector3d p2,Vector3d p3, Material* material);
	Dreieck(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d n1,Vector3d n2,Vector3d n3, Material* material);
	
	double area();
	double* getBaryzentrisch(Vector3d p);
	//double getDistance(Vector3d p);
	bool inside(Vector3d p);
	bool inside(Vector3d l1,Vector3d l2);

	Vector3d getMittelpunkt();
	Vector3d getNormale(Vector3d punkt);
	Vector3d getNormale(Vector3d punkt,Vector3d sichtVektor);
	string toString();
	string toStringBaryzentrisch(Vector3d p);
	virtual ~Dreieck();


	// Testet ob Mittelpunkt weiter links liegt (wird nur implementiert weil STL Collections einen < Operator erwarten)
	friend double operator < (  const Dreieck& d1, const Dreieck& d2) { return (d1.p1.x+d1.p2.x+d1.p3.x)<(d2.p1.x+d2.p2.x+d2.p3.x);}

	friend bool operator == ( const Dreieck& d1, const Dreieck& d2) { return d1.p1==d2.p1&&d1.p2==d2.p2&&d1.p3==d2.p3;}

};

#endif /*DREIECK_H_*/
