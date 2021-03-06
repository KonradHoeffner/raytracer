export module BoundingBox;

import Vector3d;
import Dreieck;
import SchnittEreignis;
import Log;
import <list>;
import <string>;
import <cassert>;
import <numbers>;
import <utility>;
import <algorithm>;
using std::iterator;
using std::list;
using std::string;
using std::swap;
using std::numbers::pi;

namespace std _GLIBCXX_VISIBILITY(default){} // gcc 11 and 12 bug workaround, see https://stackoverflow.com/questions/70456868/vector-in-c-module-causes-useless-bad-file-data-gcc-output

// Gesplittet wird nur, wenn mindestens so viele Dreiecke in der Box liegen
const int minPolygoneFuerSplit = 4;

template <typename T> bool PComp(T * const & a, T * const & b)
{
	return *a < *b;
}


export class BoundingBox {
public:
	// min enthält die minimalen - , max die maximalen x,y und z - Werte für die
	// eine Mitgliedschaft in der Box gilt
	Vector3d min, max;
	double distanz;

	int unterteilung;

	// Alle Dreiecke, die (teilweise) in der Box enthalten sind
	list<Dreieck *> dreiecke;

	list<BoundingBox *> kindBoxen;

	// box1 < box2 gdw. die Entfernung zu box1 ist kleiner als die zu box2
	double operator<(const BoundingBox &box) { return (distanz < box.distanz); }

	BoundingBox() {
		unterteilung = 2;
		// kindBoxen = NULL;
	}

	// Erzeugt eine Box die parallel zu den Koordinatenachsen ist mit Eckpunkten min und max
	// Spannt eine Bounding Box um eine Menge von Dreiecken auf
	BoundingBox(Vector3d min, Vector3d max, int unterteilung) {
		this->unterteilung = unterteilung;

		this->min = min;
		this->max = max;
	}

	// Spannt eine Bounding Box um eine Menge von Dreiecken auf
	BoundingBox(list<Dreieck*> dreiecke, int unterteilung) {
		this->unterteilung = unterteilung;
		this->dreiecke = dreiecke;

		min.set(0, 0, 0);
		max.set(0, 0, 0);
		int count = 0;
		for (list<Dreieck *>::iterator it = dreiecke.begin(); it != dreiecke.end();
				 it++) {
			count++;
			double xMin = std::min(
		std::min(std::min(min.x, (*it)->p1.x), (*it)->p2.x), (*it)->p3.x);
			double yMin = std::min(
		std::min(std::min(min.y, (*it)->p1.y), (*it)->p2.y), (*it)->p3.y);
			double zMin = std::min(
		std::min(std::min(min.z, (*it)->p1.z), (*it)->p2.z), (*it)->p3.z);

			double xMax = std::max(
		std::max(std::max(max.x, (*it)->p1.x), (*it)->p2.x), (*it)->p3.x);
			double yMax = std::max(
		std::max(std::max(max.y, (*it)->p1.y), (*it)->p2.y), (*it)->p3.y);
			double zMax = std::max(
		std::max(std::max(max.z, (*it)->p1.z), (*it)->p2.z), (*it)->p3.z);
			min.set(xMin, yMin, zMin);
			max.set(xMax, yMax, zMax);
		}
		logVar("Neue Bounding Box erzeugt. Polygone enthalten: ", count);
	}

	// Wie setDistanzTo aber auch für alle Nachfahren und sortiert diese gleich
	void setDistanzToRekursiv(const Vector3d &punkt) {
		setDistanzTo(punkt);
		for (list<BoundingBox *>::iterator itBox = kindBoxen.begin();
				 itBox != kindBoxen.end(); itBox++)
			(*itBox)->setDistanzToRekursiv(punkt);
		kindBoxen.sort(PComp<BoundingBox>);
	}

	// Gibt zurück ob die Box Nachfahren hat
	bool isBlatt() { return kindBoxen.empty(); }

	// Setzt die Distanz der Box zu dem gegebenen Punkt (damit man später
	// sortieren kann)
	void setDistanzTo(const Vector3d &punkt) {

		distanz = 10E10;
		double d;
		if (inside(punkt)) {
			distanz = 0;
			return;
		}

		// Auf Minimum der Distanzen zu den Eckpunkten setzen
		for (int x = 0; x < unterteilung; x++)
			for (int y = 0; y < unterteilung; y++)
	for (int z = 0; z < unterteilung; z++) {
		d = (punkt -
				 Vector3d(min.x + (max.x - min.x) * x / (unterteilung - 1),
									min.y + (max.y - min.y) * y / (unterteilung - 1),
									min.z + (max.z - min.z) * z / (unterteilung - 1)))
						.length();
		if (d < distanz)
			distanz = d;
	}

		// Wenn Distanz zu einer Ebene der Boxseiten kürzer ist als die zu den
		// Eckpunkten, dann liegt der Schnittpunkt des kürzesten Weges vom Punkt zur
		// Ebene auch auf der Seite und nicht außerhalb Edit: stimmt nicht! nur bei
		// der zugewandten seite, diese besteht aus den 4 nächsten punkten zum punkt
		// erstmal nur mit den Eckpunkten approximiert lassen

		/*d =
		distancePlanePoint(Vector3d(min.x,min.y,min.z),Vector3d(max.x,min.y,min.z),Vector3d(min.x,max.y,min.z),Vector3d
		punkt); if(d<distanz) distanz = d; d =
		distancePlanePoint(Vector3d(min.x,min.y,min.z),Vector3d(min.x,max.y,min.z),Vector3d(min.x,min.y,max.z),Vector3d
		punkt); if(d<distanz) distanz = d; d =
		distancePlanePoint(Vector3d(min.x,min.y,min.z),Vector3d(max.x,min.y,min.z),Vector3d(min.x,min.y,max.z),Vector3d
		punkt); if(d<distanz) distanz = d;

		d =
		distancePlanePoint(Vector3d(max.x,max.y,max.z),Vector3d(min.x,max.y,max.z),Vector3d(max.x,min.y,max.z),Vector3d
		punkt); if(d<distanz) distanz = d; d =
		distancePlanePoint(Vector3d(max.x,max.y,max.z),Vector3d(max.x,min.y,max.z),Vector3d(max.x,max.y,min.z),Vector3d
		punkt); if(d<distanz) distanz = d; d =
		distancePlanePoint(Vector3d(max.x,max.y,max.z),Vector3d(min.x,max.y,max.z),Vector3d(max.x,max.y,min.z),Vector3d
		punkt); if(d<distanz) distanz = d;*/
	}

	// Prüft, ob ein Punkt in der Box enthalten ist
	bool inside(Vector3d punkt) {
		return punkt.x >= min.x && punkt.x <= max.x && punkt.y >= min.y && punkt.y <= max.y && punkt.z >= min.z && punkt.z <= max.z;
	}

	// Prüft, ob eine Linie von l1 nach l2 die Bounding Box schneidet
	bool inside(Vector3d l1, Vector3d l2) {
		Vector3d l1l2 = l2 - l1;
		// Geradenparameter t, sodass der x/y/z - Wert von l1 + t*l1l2 =min.x/y/z bzw. max.x/y/z ist
		double tMinX, tMaxX, tMinY, tMaxY, tMinZ, tMaxZ, tMin, tMax;

		// Prüfung x - Wert

		if (l1l2.x != 0) // x - Wert veränderlich
		{
			tMinX = (min.x - l1.x) / l1l2.x;
			tMaxX = (max.x - l1.x) / l1l2.x;
			if (tMinX < 0 && tMaxX < 0)	return false; // Strahl fängt erst hinter Box an
			if (tMinX > tMaxX) swap(tMinX, tMaxX);
		} else // x - Wert immer gleich, hängt also nicht von t ab
		{
			if (l1.x < min.x || l1.x > max.x) return false;
			tMinX = 0;
			tMaxX = 1;
		}

		if (l1l2.y != 0) // y - Wert veränderlich
		{
			tMinY = (min.y - l1.y) / l1l2.y;
			tMaxY = (max.y - l1.y) / l1l2.y;
			if (tMinY < 0 && tMaxY < 0)	return false; // Strahl fängt erst hinter Box an
			if (tMinY > tMaxY) swap(tMinY, tMaxY);
		} else // y - Wert immer gleich, hängt also nicht von t ab
		{
			if (l1.y < min.y || l1.y > max.y) return false;
			tMinY = 0;
			tMaxY = 1;
		}

		if (l1l2.z != 0) // z - Wert veränderlich
		{
			tMinZ = (min.z - l1.z) / l1l2.z;
			tMaxZ = (max.z - l1.z) / l1l2.z;
			if (tMinZ < 0 && tMaxZ < 0) return false; // Strahl fängt erst hinter Box an
			if (tMinZ > tMaxZ) swap(tMinZ, tMaxZ);
		} else // z - Wert immer gleich, hängt also nicht von t ab
		{
			if (l1.z < min.z || l1.z > max.z) return false;
			tMinZ = 0;
			tMaxZ = 1;
		}

		// Schnittmenge der möglichen t's bestimmen
		tMin = std::max({tMinX, tMinY, tMinZ});
		tMax = std::min({tMaxX, tMaxY, tMaxZ});
		tMax = std::min(tMax, 1.0);
		return tMin < tMax;

		// return true;
	}

	/* Prüft ob Box und Dreieck sich schneiden oder ob Dreieck in Box enthalten
	ist Fall 1: Eine der Kanten p1p2, p2p3 oder p3p1 ist (teilweise) im Voxel Fall
	2: Eine der vier Hauptdiagonalen des Voxels schneidet das Dreieck
	*/
	bool inside(Dreieck dreieck) {

		// Fall 1: Eine der Kanten p1p2, p2p3 oder p3p1 ist (teilweise) im Voxel
		if (inside(dreieck.p1, dreieck.p2) || inside(dreieck.p2, dreieck.p3) ||
				inside(dreieck.p3, dreieck.p1))
			return true;
		// Fall 2: Eine der vier Hauptdiagonalen des Voxels schneidet das Dreieck

		Vector3d eckpunkte[8];

		eckpunkte[0] = min;
		eckpunkte[1] = max;
		eckpunkte[2].set(max.x, min.y, min.z);
		eckpunkte[3].set(min.x, max.y, max.z);
		eckpunkte[4].set(max.x, max.y, min.z);
		eckpunkte[5].set(min.x, min.y, max.z);
		eckpunkte[6].set(max.x, min.y, max.z);
		eckpunkte[7].set(min.x, max.y, min.z);
		for (int i = 0; i < 7; i += 2)
			if (dreieck.inside(eckpunkte[i], eckpunkte[i + 1]))
	return true;

		return false;
	}

	int offset(int x, int y, int z) {
		return x * unterteilung * unterteilung + y * unterteilung + z;
	}

	void erzeugeLeereKindBoxen() {
		if (kindBoxen.size() == 0) {
			Vector3d kindGroesse = (max - min) * (1.0 / unterteilung);
			for (int x = 0; x < unterteilung; x++)
	for (int y = 0; y < unterteilung; y++)
		for (int z = 0; z < unterteilung; z++)
			kindBoxen.push_back(new BoundingBox(
		Vector3d(min.x + kindGroesse.x * x, min.y + kindGroesse.y * y,
									 min.z + kindGroesse.z * z),
		Vector3d(min.x + kindGroesse.x * (x + 1),
									 min.y + kindGroesse.y * (y + 1),
									 min.z + kindGroesse.z * (z + 1)),
		unterteilung));
			assert(kindBoxen.size() != 0);
			assert((*kindBoxen.begin())->dreiecke.empty());
		}
	}

	void split(int tiefe) {
		if (tiefe > 0 && dreiecke.size() >= minPolygoneFuerSplit) {
			// getLogfile() << "Split durchgeführt";
			erzeugeLeereKindBoxen();
			for (list<BoundingBox *>::iterator itBox = kindBoxen.begin();
					 itBox != kindBoxen.end(); itBox++) {
	for (list<Dreieck *>::iterator itDreieck = dreiecke.begin();
			 itDreieck != dreiecke.end(); itDreieck++) {
		if ((*itBox)->inside(**itDreieck))
			(*itBox)->dreiecke.push_back(*itDreieck);
	}
	if ((*itBox)->dreiecke.empty()) {
		BoundingBox *pBox = *itBox;
		itBox--;
		kindBoxen.remove(pBox);
	} else
		(*itBox)->split(tiefe - 1);
			}
		}
	}

	std::string toString() {
		return "Min: " + min.toString() + "Max: " + max.toString() + "\n";
	}

	~BoundingBox() {}

	// Gibt zu einer Bounding Box die Kindboxen, in denen der Strahl vorkommt in
	// der Reihenfolge in der der Strahl sie passiert. Vorraussetzung: Liste der
	// Kinder ist sortiert nach Distanz (erledigt setDistanzToRekursiv()
	// automatisch aber nicht setDistanzTo() )
	list<BoundingBox *> *getGeschnitteneKindBoxenSortiert(Vector3d l1, Vector3d l2) {
		list<BoundingBox *> *pBoxen = new list<BoundingBox *>;
		return pBoxen;
		for (list<BoundingBox *>::iterator itBox = kindBoxen.begin();
				 itBox != kindBoxen.end(); itBox++) {
			if ((*itBox)->inside(l1, l2))
	pBoxen->push_back((*itBox));
		}
	}

	// Gibt an, ob der Stahl von l1 nach l2 ein Dreieck schneidet
	bool isSchnitt(Vector3d l1, Vector3d l2, double distMin, double distMax) {
		Vector3d schnittPunkt;
		l1 = l1 + ((l2 - l1).normalized() * distMin);

		if (isBlatt())
		// Schnittpunkte berechnen und den nähesten zurückgeben wenn es einen gibt
		{

			for (list<Dreieck *>::iterator it = dreiecke.begin(); it != dreiecke.end(); it++) {
	if ((**it).intersectLine(l1, l2, schnittPunkt))
		return true;
			}

		} else {
			for (list<BoundingBox *>::iterator itBox = kindBoxen.begin();
					 itBox != kindBoxen.end(); itBox++) {
	if ((*itBox)->inside(l1, l2)) {

		if ((*itBox)->isSchnitt(l1, l2, distMin, distMax))
			return true;
	}
			}
		}
		return false;
	}

	SchnittEreignis *getFirstSchnittEreignis(Vector3d l1, Vector3d l2, double distMin, double distMax) {
		SchnittEreignis *pSchnittEreignis = NULL;
		Vector3d sichtVektor = (l2 - l1).normalized();
		l1 = l1 + sichtVektor * distMin;

		Vector3d schnittPunkt;
		// double distanz	= 10E10;

		if (isBlatt())
		// Schnittpunkte berechnen und den nähesten zurückgeben wenn es einen gibt
		{
			// list<Vector3d*> liste;

			for (list<Dreieck *>::iterator it = dreiecke.begin();
					 it != dreiecke.end(); it++) {
	Dreieck *d = *it;

	if ((*d).intersectLine(l1, l1 + (sichtVektor)*distMax,
													 schnittPunkt) &&
			(schnittPunkt - l1).length() < distMax) {
		distMax = (schnittPunkt - l1).length();
		// Farbe ambient = d->material->ambient*szene.ambientehelligkeit;
		Vector3d normale;
#if defined(FLAT_SHADING)
		normale = d->n1;
#endif
#if !defined(FLAT_SHADING)
		normale = d->getNormale(schnittPunkt);
		// normale*=-1;
		if (sichtVektor.winkel(normale) < (pi / 2))
			normale *= -1;
#endif
		// normale.normalize();
		pSchnittEreignis =
				new SchnittEreignis(schnittPunkt, normale, distMax, d);
	}
			}

		} else {
			for (list<BoundingBox *>::iterator itBox = kindBoxen.begin();
					 itBox != kindBoxen.end(); itBox++) {
	if ((*itBox)->inside(l1, l2)) {

		// Schnittereignis berechnen aber noch nicht übernehmen
		SchnittEreignis *pSchnittEreignis2 =
				(*itBox)->getFirstSchnittEreignis(l1, l2, distMin, distMax);
		// Neues Schnittereignis nur übernehmen, wenn Distanz kleiner als die
		// vom Alten: pSchnittEreignis zeigt noch auf NULL -> dann ist es
		// egal, wir übernehmen einfach
		if (!pSchnittEreignis)
			pSchnittEreignis = pSchnittEreignis2;
		else
			// Es gibt schon ein Schnittereignis, existiert denn das Neue und
			// wenn ja, ist es näher dran? Dann übernehmen.
			if (pSchnittEreignis2 &&
					pSchnittEreignis2->distanz < pSchnittEreignis->distanz)
				pSchnittEreignis = pSchnittEreignis2;
		// if(pSchnittEreignis) return pSchnittEreignis;
	}
			}
		}

		/*for(list<BoundingBox*>::iterator
		itBox=kindBoxen.begin();itBox!=kindBoxen.end();itBox++)
		{
						if((*itBox)->inside(l1,l2)) pBoxen->push_back((*itBox));
		}*/
		return pSchnittEreignis;
	}
};
