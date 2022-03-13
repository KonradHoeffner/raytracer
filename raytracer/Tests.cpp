// Tests.cpp: Implementierung der Klasse Tests.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tests.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

void test(Szene& szene)
{
	getLogfile() << endl << "Tests Anfang" << endl;

	// ------------ Laden der Szene prüfen ----------------------------------------
	/*getLogfile() << "Abschwächung konstant" << szene.abschwaechung_konstant << endl;
	getLogfile() << "Abschwächung linear" << szene.abschwaechung_linear << endl;
	getLogfile() << "Abschwächung quadratisch" << szene.abschwaechung_quadratisch << endl;
	getLogfile() << "Kameraposition " << szene.kamera.position.toString();
	getLogfile() << "Kameraziel " << szene.kamera.ziel.toString();
	logVar("Kamerawinkel",szene.kamera.fovy);
	getLogfile() << "Ambiente Helligkeit" << szene.ambientehelligkeit.toString();
	getLogfile() << "Hintergrundfarbe" << szene.hintergrundfarbe.toString();*/
		
	/*for(list<Lichtquelle*>::iterator it = szene.lichtquellen.begin();it!=szene.lichtquellen.end();++it)
	getLogfile() << "Lichtquelle " << ": " << (*it)->toString();*/

	// ------------ Laden der Triangulation prüfen ----------------------------------------
	
	// Materialien

	// Dreiecke
	//getLogfile() << szene.dreiecke[0]->material->name;
	// ------------ restliche Tests -------------------------------------------------------

	/*BoundingBox box(Vector3d(0,0,0),Vector3d(10,10,10));
	box.erzeugeKindBoxen();
	int unterteilung = szene.unterteilung;
	logVar("Unterteilung",szene.unterteilung);
	for(int x=0;x<unterteilung;x++)
		for(int y=0;y<unterteilung;y++)
			for(int z=0;z<unterteilung;z++)
				getLogfile() << "Box " << x << "," << y << "," << z << ": " << box.kindBoxen[box.offset(x,y,z)].toString();
	
	Vector3d l1(5,5,-10);
	Vector3d l2(5,5,50);
	
	if(!box.inside(l1,l2)) getLogfile() << "nicht ";
	getLogfile() << "drinnen" << endl;*/
	Dreieck d(Vector3d(-5,0,0),Vector3d(0,5,0),Vector3d(5,0,0));

	/*Dreieck d1(Vector3d(-1,0,0),Vector3d(0,1,0),Vector3d(1,0,0));
	Dreieck d2(Vector3d(-5,0,0),Vector3d(0,5,0),Vector3d(5,0,0));
	Dreieck d3(Vector3d(-50,0,0),Vector3d(0,12,0),Vector3d(5,0,0));

	list<Dreieck*> dreiecke;
	dreiecke.push_back(&d);
	dreiecke.push_back(&d1);
	dreiecke.push_back(&d2);
	dreiecke.push_back(&d3);
	BoundingBox box(dreiecke);
	getLogfile() << box.toString();*/

	Vector3d punkt1(2,0,0);
	Vector3d punkt2(4,0.5,0);
	Vector3d punkt3(4,2,0);
	Vector3d punkt4(4,1,0);
	Vector3d punkt5(4,1.2,0);
	logVar("wahrtest",true);
	logVar("falschtest",false);
	logVar("punkt1",d.inside(punkt1));
	logVar("punkt2",d.inside(punkt2));
	logVar("punkt3",d.inside(punkt3));
	logVar("punkt4",d.inside(punkt4));
	logVar("punkt5",d.inside(punkt5));
	getLogfile() << d.toStringBaryzentrisch(punkt1) << d.toStringBaryzentrisch(punkt2) << d.toStringBaryzentrisch(punkt3) << d.toStringBaryzentrisch(punkt4) << d.toStringBaryzentrisch(punkt5);
	// ------------ Ende ------------------------------------------------------------------
	getLogfile() << "Tests Ende" << endl;

}