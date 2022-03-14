// Farbe.h: Class Farbe.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FARBE_H__601121F1_510F_46B5_9856_79A5E7B7FCED__INCLUDED_)
#define AFX_FARBE_H__601121F1_510F_46B5_9856_79A5E7B7FCED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

class Farbe  
{
	public:
	
	double r,g,b,a;		
	
	Farbe();
	Farbe(double r,double g,double b);
	Farbe(double r,double g,double b,double a);
	virtual ~Farbe();

	string toString();
	void set(double r,double g,double b);
	void set(double r,double g,double b,double a);
	// Sorgt dafür, dass kein Farbwert größer 1 oder kleiner 0 vorkommt
	void cap();
	// Sorgt dafür, dass kein Farbwert kleiner 0 vorkommt
	void cap_negativ();

	void operator = (const Farbe& f) {r=f.r;g=f.g;b=f.b;a=f.a;cap_negativ();}
	bool operator == (const Farbe& f) { return r==f.r&&g==f.g&&b==f.b&&a==f.a; }
	Farbe operator * (const Farbe& f) { return Farbe(r*f.r,g*f.g,b*f.b,a*f.a); }
	Farbe operator * (double d)		  {Farbe ergebnis(r*d,g*d,b*d,1);ergebnis.cap_negativ();return ergebnis;}
	Farbe operator + (const Farbe& f) {Farbe ergebnis(r+f.r,g+f.g,b+f.b,1);ergebnis.cap_negativ();return ergebnis; }
};

#endif // !defined(AFX_FARBE_H__601121F1_510F_46B5_9856_79A5E7B7FCED__INCLUDED_)
