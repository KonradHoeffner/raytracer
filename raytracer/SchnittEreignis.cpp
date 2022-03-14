// SchnittEreignis.cpp: Implementierung der Klasse SchnittEreignis.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SchnittEreignis.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

SchnittEreignis::SchnittEreignis()
{

}


SchnittEreignis::~SchnittEreignis()
{

}

SchnittEreignis::SchnittEreignis(
	Vector3d schnittPunkt,
	Vector3d normale,
	double distanz,
	Dreieck* pDreieck)
{
	this->schnittPunkt = schnittPunkt;
	this->normale = normale;
	this->distanz = distanz;
	this->pDreieck = pDreieck;
}
