// Lichtquelle.cpp: Implementierung der Klasse Lichtquelle.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lichtquelle.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Lichtquelle::Lichtquelle()
{
	position.set(0,10,0);
	farbe.set(1,1,1);
}

Lichtquelle::Lichtquelle(Vector3d position,Farbe farbe)
{
	this->position = position;
	this->farbe = farbe;
}

Lichtquelle::~Lichtquelle()
{

}

string Lichtquelle::toString()
{
	return "Lichtquelle - Position: " + position.toString() + " Farbe: " + farbe.toString();	
}