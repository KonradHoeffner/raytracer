// FileImport.h: Schnittstelle für die Klasse FileImport.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEIMPORT_H__C3BC1526_AEC4_45D0_8F73_B88EB3E32D96__INCLUDED_)
#define AFX_FILEIMPORT_H__C3BC1526_AEC4_45D0_8F73_B88EB3E32D96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

ofstream& getLogfile();
void logVar(string message, double d);
void logVar(string message, int t);
void importSzene(Szene& szene);
void importTriangulation(Szene& szene);
void logVar(string message, bool b);

#endif // !defined(AFX_FILEIMPORT_H__C3BC1526_AEC4_45D0_8F73_B88EB3E32D96__INCLUDED_)
