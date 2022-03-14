#include "stdafx.h"
#include "Dreieck.h"

Dreieck::Dreieck()
{
	material = 0;
}

Dreieck::Dreieck(Vector3d p1,Vector3d p2,Vector3d p3)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->material = NULL;
	// Normale berechnen, da wir keine Information über die umliegenden Dreiecke haben müssen wir alle Normalen gleichsetzen
	Vector3d normale = (p2-p1).cross(p3-p1);
	this->n1 = normale;
	this->n2 = normale;
	this->n3 = normale;
}

Dreieck::Dreieck(Vector3d p1,Vector3d p2,Vector3d p3, Material* material)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->material = material;
	// Normale berechnen, da wir keine Information über die umliegenden Dreiecke haben müssen wir alle Normalen gleichsetzen
	Vector3d normale = (p2-p1).cross(p3-p1);
	this->n1 = normale;
	this->n2 = normale;
	this->n3 = normale;
}

Dreieck::~Dreieck()
{
}

Dreieck::Dreieck(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d n1,Vector3d n2,Vector3d n3, Material* material)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->n1 = n1;
	this->n2 = n2;
	this->n3 = n3;


	this->material = material;
}

Vector3d Dreieck::getMittelpunkt()
{
	return 0.3334*(p1+p2+p3);
}

double Dreieck::area()
{
	return 0.5*((p3-p1).cross(p2-p1).length());
}

double* Dreieck::getBaryzentrisch(Vector3d p)
{
	double* alpha = new double[3];
	Vector3d punkte[3];
	punkte[0]=p1;
	punkte[1]=p2;
	punkte[2]=p3;
	double flaeche = area();

	// Rechnet nur Beträge aus, Vor. ist also p liegt innerhalb des Dreiecks , dann sind alle bary. Koordinaten positiv
	for(int i=0;i<3;i++)
	{
		alpha[i]=Dreieck(p,punkte[(i+1)%3],punkte[(i+2)%3]).area()/flaeche;
	}

	return alpha;
}

Vector3d Dreieck::getNormale(Vector3d punkt)
{
	double* alpha = getBaryzentrisch(punkt);
	Vector3d normale = alpha[0]*n1+alpha[1]*n2+alpha[2]*n3;
	normale.normalize();
	return normale;
}

Vector3d Dreieck::getNormale(Vector3d punkt,Vector3d sichtVektor)
{
	double* alpha = getBaryzentrisch(punkt);
	Vector3d normale = alpha[0]*n1+alpha[1]*n2+alpha[2]*n3;
	if((-sichtVektor).winkel(normale)>(PI/2)) normale*=-1;				
	normale.normalize();
	return normale;
}



bool Dreieck::inside(Vector3d p)
{
	const double epsilon = 0.0000000001;
	double flaeche1 = area();
	double flaeche2 = Dreieck(p,p2,p3).area()+Dreieck(p,p1,p2).area()+Dreieck(p,p3,p1).area();
	if(abs(flaeche1-flaeche2)<epsilon) return true;
	return false;
}

// Ist Linie von l1 nach l2 (teilweise) im Dreieck enthalten?
bool Dreieck::inside(Vector3d l1,Vector3d l2)
{
	Vector3d muell;
	return intersectDreieckLine(*this,l1,l2,muell);

}

string Dreieck::toString()
{
	return "Dreieck: Punkt1: " + p1.toString() + "Punkt2: " + p2.toString() + "Punkt3: " + p3.toString() + "\n";
}

string Dreieck::toStringBaryzentrisch(Vector3d p)
{
	double* alpha = getBaryzentrisch(p);
	char c_str[100];
	sprintf(c_str,"Gewichtung: %lf * p1 + %lf * p2 + %lf * p3 \n",alpha[0],alpha[1],alpha[2]);
	string s(c_str);
	return s;
	
}