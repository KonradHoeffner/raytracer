// Lichtquelle.h: Schnittstelle für die Klasse Lichtquelle.
//
//////////////////////////////////////////////////////////////////////

#if !defined(LICHTQUELLE_H_)
#define LICHTQUELLE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

class Lichtquelle  
{
public:
	Vector3d position;
	Farbe farbe;
	Lichtquelle();
	Lichtquelle(Vector3d position,Farbe farbe);
	// Berechnet, wieviel Licht an einem bestimmten Punkt ankommt (unter der Vorraussetzung, dass es eine Sichtlinie von der Lichtquelle zu dem Punkt gibt
	Vector3d empfangenesLicht(const Vector3d& punkt);
	string toString();
	virtual ~Lichtquelle();
};

#endif // !defined(AFX_LICHTQUELLE_H__9636B95F_01EF_43FD_A27F_D448DC681441__INCLUDED_)
