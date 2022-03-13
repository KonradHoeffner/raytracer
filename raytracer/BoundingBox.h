// BoundingBox.h: Schnittstelle für die Klasse BoundingBox.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOUNDINGBOX_H__1B01AC19_D9E5_4E13_9F5B_C15BCA316671__INCLUDED_)
#define AFX_BOUNDINGBOX_H__1B01AC19_D9E5_4E13_9F5B_C15BCA316671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

// Gesplittet wird nur, wenn mindestens so viele Dreiecke in der Box liegen
const int minPolygoneFuerSplit = 4;

class BoundingBox  
{
public:
	// min enthält die minimalen - , max die maximalen x,y und z - Werte für die eine Mitgliedschaft in der Box gilt
	Vector3d min,max;
	double distanz;

	//int tiefe;
	int unterteilung;

	// Alle Dreiecke, die (teilweise) in der Box enthalten sind
	list<Dreieck*> dreiecke;

	list<BoundingBox*> kindBoxen;

	BoundingBox();
	// Erzeugt eine Box die parallel zu den Koordinatenachsen ist mit Eckpunkten min und max
	BoundingBox(Vector3d min, Vector3d max, int unterteilung);
	// Spannt eine Bounding Box um eine Menge von Dreiecken auf
	BoundingBox(list<Dreieck*> dreiecke,int unterteilung);
	
	virtual ~BoundingBox();

	// Prüft, ob ein Punkt in der Box enthalten ist
	bool inside(Vector3d punkt);
	// Prüft, ob ein Strahl von l1 nach l2 die Bounding Box schneidet oder enthalten ist
	bool inside(Vector3d l1,Vector3d l2);
	// Prüft, ob ein Dreieck die Bounding Box schneidet oder enthalten ist
	bool inside(Dreieck dreieck);

	void erzeugeLeereKindBoxen();
	void split(int tiefe);
	// Setzt die Distanz der Box zu dem gegebenen Punkt (damit man später sortieren kann)
	void setDistanzTo(const Vector3d& punkt);
	// Wie setDistanzTo aber auch für alle Nachfahren und sortiert diese gleich
	void setDistanzToRekursiv(const Vector3d& punkt);

	// Gibt zu einer Bounding Box die Kindboxen, in denen der Strahl vorkommt in der Reihenfolge in der der Strahl sie passiert.
	// Vorraussetzung: Liste der Kinder ist sortiert nach Distanz (erledigt setDistanzToRekursiv() automatisch aber nicht setDistanzTo() )
	list<BoundingBox*>* getGeschnitteneKindBoxenSortiert(Vector3d l1,Vector3d l2);

	SchnittEreignis* getFirstSchnittEreignis(Vector3d l1,Vector3d l2,double distMin,double distMax);
	bool BoundingBox::isSchnitt(Vector3d l1,Vector3d l2,double distMin,double distMax);

	// Gibt zurück ob die Box Nachfahren hat
	bool isBlatt();
	//void loescheKindBoxen();
	string toString();
	int BoundingBox::offset(int x, int y,int z);

	// box1 < box2 gdw. die Entfernung zu box1 ist kleiner als die zu box2	
	double operator < (  const BoundingBox& box) { return (distanz<box.distanz);}

};

#endif // !defined(AFX_BOUNDINGBOX_H__1B01AC19_D9E5_4E13_9F5B_C15BCA316671__INCLUDED_)
//lalalalala