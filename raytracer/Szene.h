/* Verantwortlicher : Konrad
 * Kapselt irgendwie das ganze Szenenzeugs (Objekte, Kamera, Lichtquellen...)
 * 
*/
#ifndef SZENE_H_
#define SZENE_H_

#include "StdAfx.h"

class Szene
{
public:
	string fnTriangulation;
	string fnSzene;
	int bildBreite;
	int bildHoehe;

	double r,g,b;
	Farbe hintergrundfarbe;
	Farbe ambientehelligkeit;
	
	double abschwaechung_konstant;
	double abschwaechung_linear;
	double abschwaechung_quadratisch;

	int unterteilung; // Unterteilung für das Raumteilungsverfahren

	Kamera kamera;
	BoundingBox boundingBox;
	map<string,Material*> materialien;
	list<Dreieck*> dreiecke;
	list<Lichtquelle*> lichtquellen;
	Szene();


	virtual ~Szene();
};

#endif /*SZENE_H_*/
