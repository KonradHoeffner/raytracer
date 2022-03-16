/* Verantwortlicher : Konrad
 * Beschreibung: Kameraeinstellungen (Position, Orientierung, Field of View) */
export module Kamera;

import Vector3d;

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

	Kamera()
	{
		 clippingNear = 0.01;
		 clippingFar = 1000;
	//	 fovyGrad = 45;

		 position.set(0,0,5);
		 ziel.set(0,0,0);
		 oben.set(0,1,0);
	}

	~Kamera()
	{
	}

	// liefert normierten Vektor zurück der von der Kameraposition zum Kameraziel zeigt
	Vector3d getSichtVektor()
	{
		Vector3d v  = ziel-position;
		v.normalize();
		return v;
	}

	// liefert normierten Vektor zurück der nach rechts zeigt
	Vector3d getRechts()
	{
		Vector3d v = oben.cross(getSichtVektor());
		v.normalize();
		return v;
	}

};
