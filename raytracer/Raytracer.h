/* Verantwortlicher : Konrad
 * Beschreibung: Enthält die Hauptfunktion Raytrace. Diese wird von der main() Main.cpp mit den nötigen Parametern aufgerufen und rendert
 * dann das Bild in eine Bilddatei ohne noch irgendwelche Benutzereingaben anzufordern.
*/
#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "stdafx.h"

	void raytrace(Szene& szene);
	void zeichneDreiecke(Szene& szene);
	void zeichneLichtquellen(Szene& szene);
	void zeichneBoxen(Szene&szene);
	void zeichneNormalen(Szene& szene);
	void zeichneReflexion(Szene& szene);
	Farbe calculate(Szene& szene,Vector3d& position,Vector3d& sichtVektor,int tiefe);
	void trace();

#endif /*RAYTRACER_H_*/

