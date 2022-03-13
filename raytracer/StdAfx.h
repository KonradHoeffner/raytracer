// stdafx.h : Include-Datei f�r Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die h�ufig benutzt, aber
//      in unregelm��igen Abst�nden ge�ndert werden.
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Selten benutzte Teile der Windows-Header nicht einbinden

//Kein Warnung wg. verk�rzten Namen oder beseitigten inline-Funktionen (kann bei der STL auftreten)
#pragma warning(disable:4786)
#pragma warning(disable:4514)

const double PI=3.141592653;
//const int BILD_HOEHE = 200;
//const int BILD_BREITE = 320;
const int STRAHL_REKURSIONS_TIEFE = 4;
//#define FLAT_SHADING 
#define VORSCHAU
#define TRANSPARENZ
#define REFLEXION
//#define unterteilung 2

#include <windows.h>
#include <map>
//#include <list>
#include <cstring>
#include <vector>
#include <list>
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "tinyxml.h"

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library

#include "Vector3d.h"

using namespace std;

#include "Farbe.h"
#include "Material.h"

#include "Kamera.h"
#include "Dreieck.h"
#include "SchnittEreignis.h"
#include "BoundingBox.h"
#include "3DMath.h"
#include "Lichtquelle.h"

#include "Szene.h"
#include "FileImport.h"

#include "Raytracer.h"
#include "Tests.h"

// ZU ERLEDIGEN: Verweisen Sie hier auf zus�tzliche Header-Dateien, die Ihr Programm ben�tigt

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt zus�tzliche Deklarationen unmittelbar vor der vorherigen Zeile ein.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
