module;

#include "tinyxml2.h"

export module FileImport;

import <string>;
import <ostream>;
import <cassert>;
import Farbe;
import Log;
import Vector3d;
import Szene;

using std::string;
using std::endl;
using tinyxml2::XMLElement;
using tinyxml2::XMLNode;
using tinyxml2::XMLDocument;

//string fileNameSzene			= "abgabeszene.xml";
//string fileNameTriangulation	= "triangulationexporttest.xml";




/*Gibt erstes Kindelement mit bestimmtem Namen zurück. Erwartet, dass dieses auch existiert (Ansonsten Terminierung des Programms durch assert). */
XMLElement* getChildElementOf(XMLElement* element,string name)
{	
	XMLNode* xmlNode = element->FirstChildElement(name.c_str());
	assert( xmlNode );

	XMLElement* childElement;
	childElement = xmlNode->ToElement();
	assert( childElement  );
	return childElement;
}

// Funktioniert komischerweise nur unter angabe Aes Namens des Root - Elementes, nur doc.FirstChild() ohne parameter funktioniert nicht.
XMLElement* getRootElement(XMLDocument& doc,string name)
{
	XMLNode* xmlNode = doc.FirstChild(name.c_str());
	assert( xmlNode );
	XMLElement* childElement;
	childElement = xmlNode->ToElement();
	assert( childElement  );
	return childElement;
}

Vector3d getVector3dFromElement(XMLElement* element)
{
	assert(element);
	Vector3d v;
	element->QueryDoubleAttribute("x",&v.x);
	element->QueryDoubleAttribute("y",&v.y);
	element->QueryDoubleAttribute("z",&v.z);
	return v;
}

Farbe getFarbeFromElement3d(XMLElement* element)
{
	assert(element);
	Farbe f;
	element->QueryDoubleAttribute("r",&f.r);
	element->QueryDoubleAttribute("g",&f.g);
	element->QueryDoubleAttribute("b",&f.b);
	f.a=1;
	return f;
}

Farbe getFarbeFromElement4d(XMLElement* element)
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

	XMLDocument doc( szene.fnSzene );
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
		logfile << "Could not open XML file '" << szene.fnSzene << " Error: " << doc.ErrorDesc() << ". exiting.";
		printf( "Could not load XML file '.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		exit( 1 );
	}

	logfile << "XML Datei erfolgreich geöffnet: '" << szene.fnSzene << "'." << endl;
	
	XMLNode* xmlNode = 0;

	XMLElement* rootElement = getRootElement(doc,"szene");

	XMLElement* triangulationElement = getChildElementOf(rootElement,"triangulation");
	
	szene.fnTriangulation = *(new string(triangulationElement->Attribute("src")));
	//getLogfile() << szene.fnTriangulation << " hä?";

	XMLElement* fensterElement = getChildElementOf(rootElement,"fenster");
	fensterElement->QueryIntAttribute("breite",&szene.bildBreite);
	fensterElement->QueryIntAttribute("hoehe",&szene.bildHoehe);

	XMLElement* raumteilungElement = getChildElementOf(rootElement,"raumteilung");
	assert(raumteilungElement);
	raumteilungElement->QueryIntAttribute("unterteilung",&szene.unterteilung);

	XMLElement* kameraElement = getChildElementOf(rootElement,"kamera");

	XMLElement* kameraPositionElement = getChildElementOf(kameraElement,"position");
	szene.kamera.position = getVector3dFromElement(kameraPositionElement);

	XMLElement* kameraZielElement = getChildElementOf(kameraElement,"ziel");
	szene.kamera.ziel = getVector3dFromElement(kameraZielElement);

	XMLElement* kameraFovyElement = getChildElementOf(kameraElement,"fovy");
	kameraFovyElement->QueryDoubleAttribute("winkel",&szene.kamera.fovyGrad);
	
	szene.kamera.fovxGrad = szene.kamera.fovyGrad * szene.bildBreite / szene.bildHoehe;

	szene.kamera.fovy = szene.kamera.fovyGrad * PI / 180;
	szene.kamera.fovx = szene.kamera.fovxGrad * PI / 180;;

	XMLElement* beleuchtungElement = getChildElementOf(rootElement,"beleuchtung");

	XMLElement* hintergrundfarbeElement = getChildElementOf(beleuchtungElement,"hintergrundfarbe");
	szene.hintergrundfarbe = getFarbeFromElement3d(hintergrundfarbeElement);

	XMLElement* ambientehelligkeitElement = getChildElementOf(beleuchtungElement,"ambientehelligkeit");
	szene.ambientehelligkeit = getFarbeFromElement3d(ambientehelligkeitElement);

	XMLElement* abschwaechungElement = getChildElementOf(beleuchtungElement,"abschwaechung");
	abschwaechungElement->QueryDoubleAttribute("konstant",&szene.abschwaechung_konstant);
	abschwaechungElement->QueryDoubleAttribute("linear",&szene.abschwaechung_linear);
	abschwaechungElement->QueryDoubleAttribute("quadratisch",&szene.abschwaechung_quadratisch);

	// Alle Lichtquellen durchgehen (Alle Kinder des Elements "beleuchtung" mit dem Mamen "lichtquelle")
	int lichtquellenCount = 0;
	for(XMLNode* node = beleuchtungElement->FirstChild( "lichtquelle" );
		 node;
		 node = node->NextSibling( "lichtquelle" ) )
	{
		XMLElement* lichtquelleElement;
		lichtquelleElement = node->ToElement();
		assert(lichtquelleElement);

		XMLElement* lichtquellePositionElement = getChildElementOf(lichtquelleElement,"position");
		Vector3d lichtquellePosition = getVector3dFromElement(lichtquellePositionElement);
		
		XMLElement* lichtquelleFarbeElement = getChildElementOf(lichtquelleElement,"farbe");
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
	//XMLDocument doc( fileNameTriangulation);
	XMLDocument doc( szene.fnTriangulation);
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
		logfile << "Could not open XML file '" << szene.fnTriangulation << " Error: " << doc.ErrorDesc() << ". exiting.";
		printf( "Could not load XML file. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		exit( 1 );
	}

	logfile << "XML Datei erfolgreich geöffnet: '" << szene.fnTriangulation << "'." << endl;
	
	XMLNode* xmlNode = 0;

	XMLElement* rootElement = getRootElement(doc,"triangulation");

	// --------- Materialien -------------------------------------------------------------------
	{
	int materialienCount = 0;
	for(XMLNode* node = rootElement->FirstChild( "material" );
		 node;
		 node = node->NextSibling( "material" ) )
	{
		XMLElement* materialElement;
		materialElement = node->ToElement();
		assert(materialElement);

		string materialName = materialElement->Attribute("name");
		double glanzwert;
		Farbe ambient,diffus,spiegelnd;
		
		materialElement->QueryDoubleAttribute("glanzwert",&glanzwert);
		logVar("glanzwert",glanzwert);

		XMLElement* ambientElement = getChildElementOf(materialElement,"ambient");
		ambient = getFarbeFromElement3d(ambientElement);

		XMLElement* diffusElement = getChildElementOf(materialElement,"diffus");
		diffus = getFarbeFromElement4d(diffusElement);

		XMLElement* spiegelndElement = getChildElementOf(materialElement,"spiegelnd");
		spiegelnd = getFarbeFromElement4d(spiegelndElement);
		
		Material* material = new Material(materialName,ambient,diffus,spiegelnd,glanzwert);

		szene.materialien[materialName] = material;

		materialienCount++;
	}
	}
	// --------- Dreiecke ----------------------------------------------------------------------
	{
	int dreieckeCount = 0;
	for(XMLNode* node = rootElement->FirstChild( "dreieck" );
		 node;
		 node = node->NextSibling( "dreieck" ) )
	{
		XMLElement* dreieckElement;
		dreieckElement = node->ToElement();
		assert(dreieckElement);

		string materialName = dreieckElement->Attribute("material");

		Vector3d p1,p2,p3,n1,n2,n3;

		XMLElement* punkt1Element = getChildElementOf(dreieckElement,"punkt1");
		p1 = getVector3dFromElement(punkt1Element);

		XMLElement* punkt2Element = getChildElementOf(dreieckElement,"punkt2");
		p2 = getVector3dFromElement(punkt2Element);

		XMLElement* punkt3Element = getChildElementOf(dreieckElement,"punkt3");
		p3 = getVector3dFromElement(punkt3Element);

		XMLElement* normale1Element = getChildElementOf(dreieckElement,"normale1");
		n1 = getVector3dFromElement(normale1Element);

		XMLElement* normale2Element = getChildElementOf(dreieckElement,"normale2");
		n2 = getVector3dFromElement(normale2Element);

		XMLElement* normale3Element = getChildElementOf(dreieckElement,"normale3");
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
