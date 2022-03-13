// Material.h: Schnittstelle für die Klasse Material.
//
//////////////////////////////////////////////////////////////////////

#ifndef MATERIAL_H_
#define MATERIAL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

class Material  
{
public:

	string name;

	Farbe ambient;
	Farbe diffus;
	Farbe spiegelnd;

	double glanz;

	bool isSpiegelnd() const;
	bool isTransparent() const;

	Material();
	Material(string name, Farbe ambient, Farbe diffus, Farbe spiegelnd, double glanz);
		//Material();
	virtual ~Material();

	//friend double operator < (  const Dreieck& d1, const Dreieck& d2) { return (d1.p1.x+d1.p2.x+d1.p3.x)<(d2.p1.x+d2.p2.x+d2.p3.x);}
	bool operator ==  ( const Material& m2)
	{return ambient==m2.ambient&&diffus==m2.diffus&&spiegelnd==m2.spiegelnd&&glanz==m2.glanz&&name==m2.name;}

	/*friend bool operator ==    ( const Material& m1, const Material& m2)
	{return m1.ambient==m2.ambient&&m1.diffus==m2.diffus&&m1.spiegelnd==m2.spiegelnd&&m1.glanz==m2.glanz&&m1.mattigkeit==m2.mattigkeit&&
	m1.undurchsichtigkeit==m2.undurchsichtigkeit&&m1.name==m2.name;}*/

};

#endif
