module;

#include "tinyxml2.h"

export module FileImport;

import <string>;
import <fstream>;
import Farbe;
import Vector3d;
import Szene;

using std::ofstream;
using std::string;
using std::endl;

//string fileNameSzene			= "abgabeszene.xml";
//string fileNameTriangulation	= "triangulationexporttest.xml";

string fileNameLogfile("logfile.txt"); 
ofstream logfile(fileNameLogfile.c_str());

ofstream& getLogfile()
{
	return logfile;
}

// Schreibt Inhalt einer Variablen ins Logfile
void logVar(string message, double d)
{
	logfile << message << ": " << d << endl;
}

// Schreibt Inhalt einer Variablen ins Logfile
void logVar(string message, int i)
{
	logfile << message << ": " << i << endl;
}

void logVar(string message, bool b)
{
	logfile << message << ": ";
	logfile << (b?"wahr":"falsch"); 
	logfile << endl;
}



/*Gibt erstes Kindelement mit bestimmtem Namen zurück. Erwartet, dass dieses auch existiert (Ansonsten Terminierung des Programms durch assert). */
TiXmlElement* getChildElementOf(TiXmlElement* element,string name)
{	
	TiXmlNode* xmlNode = element->FirstChildElement(name);
	assert( xmlNode );

	TiXmlElement* childElement;
	childElement = xmlNode->ToElement();
	assert( childElement  );
	return childElement;
}

// Funktioniert komischerweise nur unter angabe Aes Namens des Root - Elementes, nur doc.FirstChild() ohne parameter funktioniert nicht.
TiXmlElement* getRootElement(TiXmlDocument& doc,string name)
{
	TiXmlNode* xmlNode = doc.FirstChild(name);
	assert( xmlNode );
	TiXmlElement* childElement;
	childElement = xmlNode->ToElement();
	assert( childElement  );
	return childElement;
}

Vector3d getVector3dFromElement(TiXmlElement* element)
{
	assert(element);
	Vector3d v;
	element->QueryDoubleAttribute("x",&v.x);
	element->QueryDoubleAttribute("y",&v.y);
	element->QueryDoubleAttribute("z",&v.z);
	return v;
}

Farbe getFarbeFromElement3d(TiXmlElement* element)
{
	assert(element);
	Farbe f;
	element->QueryDoubleAttribute("r",&f.r);
	element->QueryDoubleAttribute("g",&f.g);
	element->QueryDoubleAttribute("b",&f.b);
	f.a=1;
	return f;
}

Farbe getFarbeFromElement4d(TiXmlElement* element)
{
	assert(element);
	Farbe f;
	element->QueryDoubleAttribute("r",&f.r);
	element->QueryDoubleAttribute("g",&f.g);
	element->QueryDoubleAttribute("b",&f.b);
	element->QueryDoubleAttribute("a",&f.a);
	return f;
}

void importSzene(Szene& szene)
{

	TiXmlDocument doc( szene.fnSzene );
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
		logfile << "Could not open XML file '" << szene.fnSzene << " Error: " << doc.ErrorDesc() << ". exiting.";
		printf( "Could not load XML file '.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		exit( 1 );
	}

	logfile << "XML Datei erfolgreich geöffnet: '" << szene.fnSzene << "'." << endl;
	
	TiXmlNode* xmlNode = 0;

	TiXmlElement* rootElement = getRootElement(doc,"szene");

	TiXmlElement* triangulationElement = getChildElementOf(rootElement,"triangulation");
	
	szene.fnTriangulation = *(new string(triangulationElement->Attribute("src")));
	//getLogfile() << szene.fnTriangulation << " hä?";

	TiXmlElement* fensterElement = getChildElementOf(rootElement,"fenster");
	fensterElement->QueryIntAttribute("breite",&szene.bildBreite);
	fensterElement->QueryIntAttribute("hoehe",&szene.bildHoehe);

	TiXmlElement* raumteilungElement = getChildElementOf(rootElement,"raumteilung");
	assert(raumteilungElement);
	raumteilungElement->QueryIntAttribute("unterteilung",&szene.unterteilung);

	TiXmlElement* kameraElement = getChildElementOf(rootElement,"kamera");

	TiXmlElement* kameraPositionElement = getChildElementOf(kameraElement,"position");
	szene.kamera.position = getVector3dFromElement(kameraPositionElement);

	TiXmlElement* kameraZielElement = getChildElementOf(kameraElement,"ziel");
	szene.kamera.ziel = getVector3dFromElement(kameraZielElement);

	TiXmlElement* kameraFovyElement = getChildElementOf(kameraElement,"fovy");
	kameraFovyElement->QueryDoubleAttribute("winkel",&szene.kamera.fovyGrad);
	
	szene.kamera.fovxGrad = szene.kamera.fovyGrad * szene.bildBreite / szene.bildHoehe;

	szene.kamera.fovy = szene.kamera.fovyGrad * PI / 180;
	szene.kamera.fovx = szene.kamera.fovxGrad * PI / 180;;

	TiXmlElement* beleuchtungElement = getChildElementOf(rootElement,"beleuchtung");

	TiXmlElement* hintergrundfarbeElement = getChildElementOf(beleuchtungElement,"hintergrundfarbe");
	szene.hintergrundfarbe = getFarbeFromElement3d(hintergrundfarbeElement);

	TiXmlElement* ambientehelligkeitElement = getChildElementOf(beleuchtungElement,"ambientehelligkeit");
	szene.ambientehelligkeit = getFarbeFromElement3d(ambientehelligkeitElement);

	TiXmlElement* abschwaechungElement = getChildElementOf(beleuchtungElement,"abschwaechung");
	abschwaechungElement->QueryDoubleAttribute("konstant",&szene.abschwaechung_konstant);
	abschwaechungElement->QueryDoubleAttribute("linear",&szene.abschwaechung_linear);
	abschwaechungElement->QueryDoubleAttribute("quadratisch",&szene.abschwaechung_quadratisch);

	// Alle Lichtquellen durchgehen (Alle Kinder des Elements "beleuchtung" mit dem Mamen "lichtquelle")
	int lichtquellenCount = 0;
	for(TiXmlNode* node = beleuchtungElement->FirstChild( "lichtquelle" );
		 node;
		 node = node->NextSibling( "lichtquelle" ) )
	{
		TiXmlElement* lichtquelleElement;
		lichtquelleElement = node->ToElement();
		assert(lichtquelleElement);

		TiXmlElement* lichtquellePositionElement = getChildElementOf(lichtquelleElement,"position");
		Vector3d lichtquellePosition = getVector3dFromElement(lichtquellePositionElement);
		
		TiXmlElement* lichtquelleFarbeElement = getChildElementOf(lichtquelleElement,"farbe");
		Farbe lichtquelleFarbe = getFarbeFromElement3d(lichtquelleFarbeElement);

		//Lichtquelle* lichtquelle = new Lichtquelle(lichtquellePosition,lichtquelleFarbe);
		//szene.lichtquellen.push_back(lichtquelle);
		
		szene.lichtquellen.push_back(new Lichtquelle(lichtquellePosition,lichtquelleFarbe));
		

		lichtquellenCount++;
	}
	logVar("Anzahl Lichtquellen geladen: ",lichtquellenCount);

	/*xmlNode = doc.FirstChild( "szene" );
	assert( xmlNode );
	rootElement = xmlNode->ToElement();
	assert( rootElement  );*/




}

void importTriangulation(Szene& szene)
{
	//TiXmlDocument doc( fileNameTriangulation);
	TiXmlDocument doc( szene.fnTriangulation);
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
		logfile << "Could not open XML file '" << szene.fnTriangulation << " Error: " << doc.ErrorDesc() << ". exiting.";
		printf( "Could not load XML file. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		exit( 1 );
	}

	logfile << "XML Datei erfolgreich geöffnet: '" << szene.fnTriangulation << "'." << endl;
	
	TiXmlNode* xmlNode = 0;

	TiXmlElement* rootElement = getRootElement(doc,"triangulation");

	// --------- Materialien -------------------------------------------------------------------
	{
	int materialienCount = 0;
	for(TiXmlNode* node = rootElement->FirstChild( "material" );
		 node;
		 node = node->NextSibling( "material" ) )
	{
		TiXmlElement* materialElement;
		materialElement = node->ToElement();
		assert(materialElement);

		string materialName = materialElement->Attribute("name");
		double glanzwert;
		Farbe ambient,diffus,spiegelnd;
		
		materialElement->QueryDoubleAttribute("glanzwert",&glanzwert);
		logVar("glanzwert",glanzwert);

		TiXmlElement* ambientElement = getChildElementOf(materialElement,"ambient");
		ambient = getFarbeFromElement3d(ambientElement);

		TiXmlElement* diffusElement = getChildElementOf(materialElement,"diffus");
		diffus = getFarbeFromElement4d(diffusElement);

		TiXmlElement* spiegelndElement = getChildElementOf(materialElement,"spiegelnd");
		spiegelnd = getFarbeFromElement4d(spiegelndElement);
		
		Material* material = new Material(materialName,ambient,diffus,spiegelnd,glanzwert);

		szene.materialien[materialName] = material;

		materialienCount++;
	}
	}
	// --------- Dreiecke ----------------------------------------------------------------------
	{
	int dreieckeCount = 0;
	for(TiXmlNode* node = rootElement->FirstChild( "dreieck" );
		 node;
		 node = node->NextSibling( "dreieck" ) )
	{
		TiXmlElement* dreieckElement;
		dreieckElement = node->ToElement();
		assert(dreieckElement);

		string materialName = dreieckElement->Attribute("material");

		Vector3d p1,p2,p3,n1,n2,n3;

		TiXmlElement* punkt1Element = getChildElementOf(dreieckElement,"punkt1");
		p1 = getVector3dFromElement(punkt1Element);

		TiXmlElement* punkt2Element = getChildElementOf(dreieckElement,"punkt2");
		p2 = getVector3dFromElement(punkt2Element);

		TiXmlElement* punkt3Element = getChildElementOf(dreieckElement,"punkt3");
		p3 = getVector3dFromElement(punkt3Element);

		TiXmlElement* normale1Element = getChildElementOf(dreieckElement,"normale1");
		n1 = getVector3dFromElement(normale1Element);

		TiXmlElement* normale2Element = getChildElementOf(dreieckElement,"normale2");
		n2 = getVector3dFromElement(normale2Element);

		TiXmlElement* normale3Element = getChildElementOf(dreieckElement,"normale3");
		n3 = getVector3dFromElement(normale3Element);
		
		Dreieck* pDreieck = new Dreieck(p1,p2,p3,n1,n2,n3,szene.materialien[materialName]);

		szene.dreiecke.push_back(pDreieck);

		//getLogfile() << "Punkt 1: "<< p1.toString();

//		szene.materialien[materialName] = material;

		dreieckeCount++;
	}
	logVar("Anzahl Dreiecke geladen: ",dreieckeCount);
	}
	// Bounding Box erzeugen
	szene.boundingBox = BoundingBox(szene.dreiecke,szene.unterteilung);
	szene.boundingBox.split(8);
	//szene.boundingBox.setDistanzToRekursiv(szene.kamera.position);	
}
