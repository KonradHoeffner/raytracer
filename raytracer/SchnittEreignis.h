// SchnittEreignis.h: Schnittstelle für die Klasse SchnittEreignis.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SCHNITTEREIGNIS_H_)
#define SCHNITTEREIGNIS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SchnittEreignis  
{
public:
//	bool isGeschnitten;
	Vector3d schnittPunkt;
//	Vector3d reflexionsVektor;
	Vector3d normale;
	double distanz;
	Dreieck* pDreieck;

// Material& material;
	
	
	SchnittEreignis(
		Vector3d schnittPunkt,
		Vector3d normale,
		double distanz,
		Dreieck* pDreieck);

	SchnittEreignis();
	virtual ~SchnittEreignis();

};

#endif // !defined(SchnittEreignis_H)
