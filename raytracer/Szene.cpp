export module Szene;

import Farbe;
import Kamera;
import BoundingBox;
import Lichtquelle;
import Dreieck;
import Material;
import <list>;
import <string>;
import <map>;
import <list>;
using std::string;
using std::map;
using std::list;
namespace std _GLIBCXX_VISIBILITY(default){} // gcc 11 and 12 bug workaround, see https://stackoverflow.com/questions/70456868/vector-in-c-module-causes-useless-bad-file-data-gcc-output

export class Szene
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

	Szene()
	{
		fnSzene = "abgabeszene.xml";
	}

	virtual ~Szene();
};
