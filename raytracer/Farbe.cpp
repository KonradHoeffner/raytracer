// Farbe.cpp: Implementierung der Klasse Farbe.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Farbe.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Farbe::Farbe()
{
	r=1;
	g=1;
	b=1;
	a=1;
}

Farbe::Farbe(double r,double g,double b)
{
	this->r=r;
	this->g=g;
	this->b=b;
	a=1;
	cap_negativ();
}

Farbe::Farbe(double r,double g,double b,double a)
{
	this->r=r;
	this->g=g;
	this->b=b;
	this->a=a;
	cap_negativ();
}

Farbe::~Farbe()
{

}

string Farbe::toString()
{
	char c_str[50];
	sprintf(c_str," r: %lf g: %lf b: %lf a: %lf",r,g,b,a);
	string s(c_str);
	return s;
}

void Farbe::set(double r,double g,double b)
{
	this->r=r;
	this->g=g;
	this->b=b;
	a=1;
	cap_negativ();
}

void Farbe::set(double r,double g,double b,double a)
{
	this->r=r;
	this->g=g;
	this->b=b;
	this->a=a;
	cap_negativ();
}

void Farbe::cap()
{
	r = max(min(r,1),0);
	g = max(min(g,1),0);
	b = max(min(b,1),0);
	a = max(min(a,1),0);
}

void Farbe::cap_negativ()
{
	r = max(r,0);
	g = max(g,0);
	b = max(b,0);
	a = max(a,0);
}
