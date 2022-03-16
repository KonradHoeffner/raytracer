#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Selten benutzte Teile der Windows-Header nicht einbinden

//Kein Warnung wg. verkürzten Namen oder beseitigten inline-Funktionen (kann bei der STL auftreten)
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

#include <map>
#include <cstring>
#include <vector>
#include <list>
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "tinyxml.h"

#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glu.h>			// Header File For The GLu32 Library
#include <GL/glut.h>

using namespace std;

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
