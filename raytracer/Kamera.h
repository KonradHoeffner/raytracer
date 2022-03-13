/* Verantwortlicher : Konrad
 * Beschreibung: Kameraeinstellungen (Position, Orientierung, Field of View)
*/
#ifndef KAMERA_H_
#define KAMERA_H_

#include "StdAfx.h"

class Kamera
{
public:

	// Alles was näher an der Kamera ist wird geclippt 
	 double clippingNear;
	// Alles was weiter weg von der Kamera ist wird geclippt
	 double clippingFar;

	 double fovyGrad;
	 double fovxGrad;

	 // Winkel in Bogenmaß, der den Sichtwinkel in Y - Richtung angibt. Muss zwischen 0 und pi liegen
	 double fovy;
	// Winkel in Bogenmaß, der den Sichtwinkel in X - Richtung angibt. Muss zwischen 0 und pi liegen
	 double fovx;

	 // Dort steht die Kamera
	 Vector3d position;
	// Dort zeigt die Kamera hin
	 Vector3d ziel;
	// Zeigt nach oben
	 Vector3d oben;

	Kamera();
	virtual ~Kamera();
	
	// liefert normierten Vektor zurück der von der Kameraposition zum Kameraziel zeigt
	Vector3d getSichtVektor();
	// liefert normierten Vektor zurück der nach rechts zeigt
	Vector3d getRechts();
};

#endif /*KAMERA_H_*/
